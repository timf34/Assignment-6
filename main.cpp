#include <iostream>
#include <fstream>
#include <string>
#include "node.hpp"
using namespace std;

bool build_tree(string new_word, string next_word, node*& tree);
void search_word(string word, node* tree);
void print_word_and_pair_count(string word, node* location);
void build_pair_tree (string next_word, node*& pair_tree);
void search_word_pairs(string word, node*& root);
void print_pair_word(node* location);

int main() {

  string file_name;
  string word, current_word, next_word, first_word;
  ifstream myfile;
  int total_count{0}, individual_word_count{0};
  bool file_opens = false;

  node* root = nullptr;

  while(file_opens == false){
    cout << "Please enter the name of the book file:" << endl;
    //cin >> file_name;
    file_name = "sample.txt";

    myfile.open(file_name);

    if(!myfile.is_open()){
      cout << "An error occurred attempting to open the file \"" << file_name << "\"." << endl;
    }
    else{
      myfile >> first_word;
      //my_file >> word;
      int i=0;
      while(myfile >> word){
        if(i==0){
          current_word = first_word;
          next_word = word;
          i++; //this avoids getting a really large i by putting the counter here, it will stop at 1!
        }
        else{
          current_word = next_word;
          next_word=word;
        }
        //cout << current_word << " " << i << " " << next_word << endl;

        if(myfile.fail()){
          cout << "failed";
        }
        total_count++;
        if(build_tree(current_word, next_word, root)){
          individual_word_count++;
        }
        
      }
      file_opens=true;
      current_word = next_word;
    }

  }
  cout << "The file \"" << file_name << "\" contains " <<total_count << " words of which " << individual_word_count << " are distinct." << endl;


  while(cin.eof()==false){
    cout << "Please enter the word you wish to check:" << endl;
    cin >> word;
    if (cin.eof()==true){
      break; //not the most elegant way (it makes the while loop condition a bit pointless) to exit fully but it works 
    }
    search_word(word, root);
  }


  cout << "Goodbye" << endl;

  return 0;
}

bool build_tree(string new_word, string next_word, node*& tree){
  bool response;

	if (tree == nullptr) {
		tree = new node();
    tree->assign(new_word);
    //tree->pair_tree_root->assign(next_word); This was causing the errors! be careful, use VCS when changing strategy so as not to leave anything straggling!!!!
    tree->total_pairs++;
		build_pair_tree(next_word, tree->pair_tree_root);
    response = true; // it is a new word
	} else {
		if (new_word == *tree) {
			tree->count++;
      tree->total_pairs++;
			response = false; // it is not a new word
      build_pair_tree(next_word, tree->pair_tree_root);
      //cout << new_word << ": " << tree->count <<endl;
		} else {
			if (new_word < *tree) {
				response = build_tree(new_word, next_word, tree->before);
			} else {
				response = build_tree(new_word, next_word, tree->after);
			}
		}
	}
	return response;
}

void build_pair_tree(string next_word, node*& tree){
  node* placeholder = tree;

  if (tree == nullptr){
    node* first_pair = new node();
    first_pair->assign(next_word);
    tree = first_pair;
    tree->pair_dup_count++;
  }
  else if (next_word == *placeholder){
    tree->pair_dup_count++;
  }
  else if (next_word < *placeholder){
    build_pair_tree(next_word, placeholder->before);
  }
  else if(next_word > *placeholder){
    build_pair_tree(next_word, placeholder->after);
  }
}


void search_word(string word, node* tree){

  if(tree == nullptr){
    cout << "The word \"" << word << "\" was not found." << endl;
    return;
  }
  
  if (*tree == word){
    print_word_and_pair_count(word, tree);
    tree = tree->pair_tree_root;
    search_word_pairs(word, tree);
    return;
  }
  else{
    if (word < *tree) {
      search_word(word, tree->before);
    } else{
      search_word(word, tree->after);
    }
  }
}

void print_word_and_pair_count(string word, node* location){
  int count = location->total_pairs;

  cout << "Word pairs starting with \"" << word << "\" were found ";
  if (count == 1){
   cout << "once."<< endl;
  }
  else if(count == 2){
    cout << "twice."<< endl;
  }
  else{
    cout << count << " times." << endl;
  }

}
void print_pair_word(node* location){
  int count = location->pair_dup_count;

  cout << "The word \"" << *location << "\" was found ";
  if (count == 1){
   cout << "once."<< endl;
  }
  else if(count == 2){
    cout << "twice."<< endl;
  }
  else{
    cout << count << " times." << endl;
  }

}

void search_word_pairs(string word, node*& root){

  if (root != nullptr) {
    search_word_pairs(word, root->before);
    print_pair_word(root);
    search_word_pairs(word, root->after);
  }

}
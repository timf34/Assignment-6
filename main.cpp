#include <iostream>
#include <fstream>
#include <string>
#include "node.hpp"
using namespace std;

bool build_tree(string new_word, string next_word, node*& tree);
void search_word(string word, node* tree);
void print_word(string word, node* location);
void build_pair_tree (string next_word, node*& pair_tree);

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
    //cout << tree->pair_tree_root << endl;
    cout << new_word << " ";
		build_pair_tree(next_word, tree->pair_tree_root);
    response = true; // it is a new word
    //cout << new_word << endl;
	} else {
		if (new_word == *tree) {
			tree->count++;
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
//USE VCS!!!!
void build_pair_tree(string next_word, node*& tree){
  node* placeholder = tree;
  //cout << endl << "placeholder: " << placeholder << endl;

  if (tree == nullptr){
    node* first_pair = new node();
    first_pair->assign(next_word);
    tree= first_pair;
    cout << next_word << endl;
    //cout << next_word << " " << tree->pair_tree_root << endl;
  
  }
  else if (next_word == *placeholder){
    cout << "repeated pair !!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
  }
  else if (next_word < *placeholder){
    //node* placeholder = tree->pair_tree_root;
    cout << " somehtg " << endl;
    build_pair_tree(next_word, placeholder->before);
  }
  else if(next_word > *placeholder){
    //node* placeholder = tree->pair_tree_root;
     cout << next_word << " " << *placeholder << " somehtg 3 " << placeholder->after << endl;
     node* p_after = placeholder->after;
    build_pair_tree(next_word, p_after);
  }
}

/*void print_pair_tree(node *tree){
  if (tree != nullptr) {
    print_pair_tree(tree->before);
    cout << "\"" << *tree <<"\" " << tree->count << endl;
    print_pair_tree(tree->after);
  }
}*/

/*void print_pairs(string word, node* tree){

  if(tree == nullptr){
    cout << "The word \"" << word << "\" was not found." << endl;
    return;
  }
  
  if (*tree == word){
    print_word(word, tree);
    return;
  }
  else{
    if (word < *tree) {
      search_word(word, tree->before);
    } else {
      search_word(word, tree->after);
    }
  }
}*/

void search_word(string word, node* tree){

  if(tree == nullptr){
    cout << "The word \"" << word << "\" was not found." << endl;
    return;
  }
  
  if (*tree == word){
    print_word(word, tree);
    return;
  }
  else{
    if (word < *tree) {
      search_word(word, tree->before);
    } else {
      search_word(word, tree->after);
    }
  }
}

void print_word(string word, node* location){
  int count = location->count;

  cout << "The word \"" << word << "\" was found ";
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


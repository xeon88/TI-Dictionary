#include "Queue.h"
#define MAX_NUM_CHILDS 5

 class WordDictionary
{

        pNode root;
        int total;
        int max_branching_factor;

		int get_total();
		int get_branching();
		void set_total();
        pNode add_r_word(pNode p, int lvl , int branching , std::string word, std::string prefix, bool h);
        void search_node(char s , int lvl);
        void print_dictionary(pNode root);
        void dictionary_entropy(pNode root, int max_level);
        pNode * possibilities(pNode p);
        pNode search_path(pNode root,std::string prefix, int current_level);


	public:

		WordDictionary();
		~WordDictionary();
		void add_word(std::string word);
        void view();
        int get_branching_factor();
        int total_word();
        void entropy(int max_level);
        void predictive_keyboard();
        void Order_dictionary();
        void print_most_prob_chars(std::string prefix);
        void w_print_most_prob_chars(std::string prefix);
        void keyboard();
};

/*

*/


void destroy_win(WINDOW *local_win);

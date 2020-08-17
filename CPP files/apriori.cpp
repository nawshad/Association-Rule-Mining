/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   apriori.cpp
 * Author: nawshad farruque
 *
 * Created on February 6, 2017, 11:12 PM
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <map>
#include <string>
#include <cmath>

using namespace std;

/*
 * This algorithm looks into the transactions and find the itemsets having 
 * support above a certain level. 
 * 
 */

string comma_seperated_list(vector<int> vector_of_ints){
    string s;
    for(int i=0; i<vector_of_ints.size(); i++){
        string delim = ", ";
        if(i==vector_of_ints.size()-1){
            delim = " ";
        }
        s = s + std::to_string(vector_of_ints[i])+delim;
    }
    return s;
}
    
int print_map(std::map<int,int> items, int trans_size) {
    cout<<"Frequent 1 itemsets:"<<endl;
    for (std::map<int,int>::iterator it=items.begin(); 
        it!=items.end(); ++it){
        cout<< it->first<<" "<<std::fixed << std::setprecision(2)<<"("<<(double)it->second/trans_size<<")"<<endl;
        
    }
    return 0;
}

int write_map(std::map<int, int> one_items_map, int trans_size){
    ofstream myfile;
    myfile.open ("all_one_itemsets.txt");
    for (std::map<int,int>::iterator it=one_items_map.begin(); 
        it!=one_items_map.end(); ++it){
        myfile<< it->first<<" "<<std::fixed << std::setprecision(2)<<"("<<(double)it->second/trans_size<<")"<<endl;
    }
    return 0;
    myfile.close();
}

int print_map_with_vector_keys(std::map<vector<int> ,int> items, int trans_size){
    for (std::map<vector<int>,int>::iterator it=items.begin(); 
        it!=items.end(); ++it){
            for(int i=0; i<it->first.size(); i++){
                cout<<it->first[i]<<" ";
            }
            cout<<std::fixed << std::setprecision(2)<<"("<<(double)it->second/trans_size<<")"<<endl;
    }
    return 0;
}

int write_L_final(std::map<vector<int> ,int> items, int count_itemsets, int trans_size){
        ofstream myfile;
        myfile.open ("all_freq_itemsets.txt");
        
        for(int i=2; i<count_itemsets; i++){ 
            myfile<<"Frequent "<<i<<" itemsets: "<<endl;
            for (std::map<vector<int>,int>::iterator it=items.begin(); 
            it!=items.end(); ++it){  
                // Since this container holds the itemsets with size starting with 2 it will start with 
                //freq 2 itemsets.
                if(it->first.size() == i){
                    for(int j=0; j<it->first.size(); j++){
                        myfile<<it->first[j]<<" ";
                    }
                    myfile<<std::fixed << std::setprecision(2)<<"("<<(double)it->second/trans_size<<")"<<endl;
                }
            }
        }
        myfile.close();
        return 0;
}

int print_L_final(std::map<vector<int> ,int> items, int count_itemsets, int trans_size){
        
        for(int i=2; i<count_itemsets; i++){ 
            cout<<"Frequent "<<i<<" itemsets: "<<endl;
            for (std::map<vector<int>,int>::iterator it=items.begin(); 
            it!=items.end(); ++it){ 
                if(it->first.size() == i){
                    vector<int> vector_of_integers;
                    for(int j=0; j<it->first.size(); j++){
                        //cout<<it->first[j]<<" ";
                        vector_of_integers.push_back(it->first[j]);
                    }
                    cout<<comma_seperated_list(vector_of_integers);
                    cout<<std::fixed << std::setprecision(2)<<"("<<(double)it->second/trans_size<<")"<<endl;
                }
            }
        }
        
        return 0;
}

int print_vector_of_vectors(vector<vector<int> > items){
    for(int i=0; i<items.size(); i++){
        for(int j=0; j<items[i].size(); j++){
            cout<< items[i][j] <<" ";
        }
        cout<<endl;
    }
    return 0;
}

int print_vector(vector<int> items){
    for(int i=0; i<items.size(); i++){
        cout<<items[i]<<endl;
    }
    return 0;
}

void save(vector<int> l, vector<vector<int> > &vector_of_n_items){
    vector_of_n_items.push_back(l);
}

//The following code was collected from StackOverFlow and provided by the user Marcog
//http://stackoverflow.com/questions/4555565/generate-all-subsets-of-size-k-from-a-set

void subset(vector<int> arr, int left, int index, vector<int> &l, vector<vector<int> > &vector_of_n_items){
    if(left==0){
        save(l, vector_of_n_items);
        return;
    }
    for(int i=index; i<arr.size();i++){
        l.push_back(arr[i]);
        subset(arr,left-1,i+1,l, vector_of_n_items);
        l.pop_back();
    }
} 

std::map<int, int> gen_one_minsup_item_counts_map(std::map<int, int> one_item_counts_map, int support_count){
    std::map<int, int> one_minsup_items;
    for (std::map<int,int>::iterator it=one_item_counts_map.begin(); 
        it!=one_item_counts_map.end(); it++){
        int key = it->first;
        int value = it->second;
        if(one_item_counts_map[key] >= support_count){
            one_minsup_items[key] = value;
        }
    }
    return one_minsup_items;
}

int write_Tids_Items_to_file(std::map<int, vector<vector<int> > > Tids_Items){
    ofstream myfile;
    myfile.open ("Tid_Items.txt");
    
    for (std::map<int, vector<vector<int> > >::iterator it=Tids_Items.begin(); 
        it!=Tids_Items.end(); ++it){
        myfile<< it->first<<"->"<<endl;
        vector<vector<int> > Tids = it->second;
        for(int i=0; i<Tids.size(); i++){
                for(int j=0; j<Tids[i].size(); j++){
                    myfile<<Tids[i][j]<<" ";
                }
                myfile<<endl;
        }
    }
    myfile.close();
    return 0;
}

// The following function getAllSubsets  was collected from StackOverFlow, and provided by Ronald Rey
//http://stackoverflow.com/questions/728972/finding-all-the-subsets-of-a-set
vector< vector<int> > gen_all_subsets(vector<int> itemset)
{
    vector< vector<int> > subset;
    vector<int> empty;
    subset.push_back(empty);

    for (int i = 0; i < itemset.size(); i++)
    {
        vector< vector<int> > subsetTemp = subset;

        for (int j = 0; j < subsetTemp.size(); j++)
            subsetTemp[j].push_back( itemset[i] );

        for (int j = 0; j < subsetTemp.size(); j++)
            subset.push_back( subsetTemp[j] );
    }
    return subset;
}

double minconf(int count_numer, int count_denom){
    
    double minconf_value = (double)count_numer/(double)count_denom;
    return minconf_value;
}

int gen_strong_association_rule(std::map<vector<int>,int> L_final, 
                                int trans_size, std::map<int, int> one_minsup_item_counts_map, 
                                double conf_threshold, string c){
    
    ofstream myfile;
    myfile.open ("strong_rules.txt");
    
    int no_of_strong_rules = 0;
    
    for (std::map<vector<int>, int>::iterator it=L_final.begin(); it!=L_final.end(); ++it){
        vector<vector<int> > freq_sets_subsets = gen_all_subsets(it->first);
      
        for(int i=1; i<freq_sets_subsets.size()-1; i++){
             vector<int> diff;
             std::set_difference(it->first.begin(), it->first.end(), 
                                 freq_sets_subsets[i].begin(), freq_sets_subsets[i].end(),back_inserter(diff));
                
                vector<int> numer = it->first;
                vector<int> denom = freq_sets_subsets[i];
              
                int count_denom = 0;
                if(denom.size() == 1){
                    count_denom = one_minsup_item_counts_map[denom[0]];
                }else{
                    count_denom = L_final[denom];
                }
                
                int count_numer = 0;
                count_numer = L_final[numer];

                double minconf_val = minconf(count_numer, count_denom); 
                
                
                if(minconf_val >= conf_threshold){
                    vector<int> vector_of_int;
                    for(int j=0; j<freq_sets_subsets[i].size(); j++){
                        vector_of_int.push_back(freq_sets_subsets[i][j]);
                    }
                    myfile<<comma_seperated_list(vector_of_int);
                        if(c=="r" || c=="a"){
                            cout<<comma_seperated_list(vector_of_int); 
                        }
                    myfile<<"-> ";
                    if(c=="r"||c=="a"){
                        cout<<"-> ";
                    }
                    vector_of_int.clear();
                    for(int k=0; k<diff.size(); k++){
                        vector_of_int.push_back(diff[k]);
                    }
                    
                    myfile<<comma_seperated_list(vector_of_int);
                    if(c=="r"||c=="a"){
                        cout<<comma_seperated_list(vector_of_int);
                    }
                    
                    myfile<<"("<<std::fixed << std::setprecision(2)<<(double)count_numer/trans_size<<","<<minconf_val<<")"<<endl;
                    if(c=="r"||c=="a"){
                        cout<<"("<<std::fixed << std::setprecision(2)<<(double)count_numer/trans_size<<","<<minconf_val<<")"<<endl;
                    }
                    
                    no_of_strong_rules++;
                }
            }
        }
    
    myfile.close();
    return  no_of_strong_rules;
    
}

std::map<int, vector<vector<int> > > gen_two_itemsets_trans_table(std::map<int, int> one_minsup_item_counts_map, 
                                                                  vector<vector<int> > trans_vector){
    std::map<int, vector<vector<int> > > two_itemset_trans_table;
   
    for(int i=0; i<trans_vector.size(); i++){
        vector<vector<int> > Tid_Items;
        
        for(int j=0; j<trans_vector[i].size(); j++){
            for(int k=j+1; k<trans_vector[i].size(); k++){
                vector<int> pairs;
                
                if(one_minsup_item_counts_map.count(trans_vector[i][j]) > 0 && 
                                                    one_minsup_item_counts_map.count(trans_vector[i][k]) ){
                    pairs.push_back(trans_vector[i][j]);
                    pairs.push_back(trans_vector[i][k]);
                    Tid_Items.push_back(pairs);
                }
            }
        }
       if(Tid_Items.size() > 0){
          two_itemset_trans_table[i] = Tid_Items; 
       } 
           
    } 
    
    return two_itemset_trans_table;
}

std::map<vector<int>, int> gen_n_minsups_itemsets_count_map(std::map<int, vector<vector<int> > > prev_itemset_trans_table, 
                                                             int support_count){
    std::map<vector<int>, int> n_itemsets_count_map, n_minsup_itemsets_count_map;
    
    for (std::map<int, vector<vector<int> > >::iterator it=prev_itemset_trans_table.begin(); 
        it!=prev_itemset_trans_table.end(); ++it){
        
        vector<vector<int> > n_itemsets = it->second;
        for(int i=0; i<n_itemsets.size(); i++){
           //  
            if(n_itemsets_count_map.count(n_itemsets[i]) > 0){
                n_itemsets_count_map[n_itemsets[i]]++;
                if(n_itemsets_count_map[n_itemsets[i]] >= support_count){
                    n_minsup_itemsets_count_map[n_itemsets[i]] = n_itemsets_count_map[n_itemsets[i]];
                }
            }else{
                n_itemsets_count_map[n_itemsets[i]] = 1;
            }
        }
    }
    
    return n_minsup_itemsets_count_map;
}

std::map<int, vector<vector<int> > > gen_n_itemsets_trans_table(std::map<vector<int>, int> prev_minsup_item_counts_map,
                                                                std::map<int, vector<vector<int> > > prev_itemset_trans_table){
    
    std::map<int, vector<vector<int> > > n_itemset_trans_table;
    
    //First iterate through the trans table
    //Get the values and find if they have common n-1 elements, are frequent and no subsets having
    // in-frequent. Join them, push them in a vector of vectors as if not present in the vector.
    // we should get a table of transaction id and three items now. Prune any transaction with 0
    // element vector.
    // at the end print the table and check at the beginning if we find any vector with one elements.
    // we ignore them at each iteration.
    
    int trans_index = 0;
    for (std::map<int, vector<vector<int> > >::iterator it=prev_itemset_trans_table.begin(); 
        it!=prev_itemset_trans_table.end(); ++it){
        
        vector<vector<int> > n_items = it->second;
        vector<vector<int> > Tid_Items;
        
        for(int i=0; i<n_items.size(); i++){
            for(int j=i+1; j<n_items.size(); j++){
                //for(int k=j+1; k<n_items[i].size(); k++){
                    vector<int> union_vector, intersec_vector;
                    
                    // Are frequent?
                    if(prev_minsup_item_counts_map.count(n_items[i]) > 0 && 
                            prev_minsup_item_counts_map.count(n_items[j]) > 0 ){
                        
                        
                        set_intersection(n_items[i].begin(),n_items[i].end(),
                              n_items[j].begin(), n_items[j].end(),
                              back_inserter(intersec_vector));
                        
                        //have n-1 common elements?
                        
                        if((intersec_vector.size() == n_items[i].size()-1)){
                        set_union(n_items[i].begin(), n_items[i].end(),
                                     n_items[j].begin(), n_items[j].end(),back_inserter(union_vector));
                        

                            vector<int> lt;  
                            vector<vector<int> > vector_of_n_sub_items;
                            subset(union_vector,union_vector.size()-1,0,lt,vector_of_n_sub_items); 

                            //find if any of the n_sub_items is not in n-1 (prev)_itemsets;
                            bool find = true;
                            for(int k=0; k<vector_of_n_sub_items.size(); k++){
                                if(prev_minsup_item_counts_map.count(vector_of_n_sub_items[k]) == 0){
                                    find = false;
                                    break;
                                }
                            }
                            
                            //if find push that item in a vector 
                            if(find){
                                //find if that vector already exists
                                if(!(std::find(Tid_Items.begin(), Tid_Items.end(), 
                                        union_vector) != Tid_Items.end())){
                                        Tid_Items.push_back(union_vector);  
                                }
                                
                            }
                        }    
                    }
                }
           
            }
        
        if(Tid_Items.size()>0){
            n_itemset_trans_table[trans_index] =   Tid_Items;
        }
        trans_index++;
    }
   //write_Tids_Items_to_file(n_itemset_trans_table);  
   return  n_itemset_trans_table;
    
}

int freq_itemset_generator(string filename, double sup_threshold, double conf_threshold, string c){
    //read the file and store all one items, sort them and store in a vector and also, save all
    //the transactions in a vector of vectors.
     
    std::ifstream file(filename);
    std::string line; 
    std::string item;
    vector<int> indv_items_vector, one_unique_items;
    vector< vector<int> > trans_vector;
    std::map<int, int> one_item_counts_map;
    
    while (std::getline(file, line)){
        //cout<<"line:"<<line<<endl;
        indv_items_vector.clear();
        istringstream iss(line, istringstream::in);
        while( iss >> item ) { 
            //cout<<item<<endl;
            int int_item = std::stoi(item); 
            if(one_item_counts_map.count(int_item) > 0){
                one_item_counts_map[int_item]++; //count increased
            }else{
                one_item_counts_map[int_item] = 1;
            }
            indv_items_vector.push_back(int_item);
        }
        trans_vector.push_back(indv_items_vector);
    }
    
    ofstream myfile;
    myfile.open ("stats.txt");
    myfile<<"Operating on file: "<<filename<<endl;
    
    vector<int> freq_itemset_counts;
    
    myfile<<"Transaction Size: "<<trans_vector.size()<<endl;
    //cout<<"Transaction Size:"<<trans_vector.size()<<endl;
    
    int support_count = round(trans_vector.size()*(sup_threshold));
    
    myfile<<"Support count: "<<support_count<<endl;
    
    std::map<int, int> one_minsup_item_counts_map = gen_one_minsup_item_counts_map(one_item_counts_map, support_count);
    
    //print_map(one_minsup_item_counts_map);
    
    myfile<<"Frequent 1 itemset size: "<<one_minsup_item_counts_map.size()<<endl; 
    
    freq_itemset_counts.push_back(one_minsup_item_counts_map.size());
    
    //myfile<<"One minsup map write to file"<<endl;
     
    std::map<int, vector<vector<int> > > two_itemsets_trans_table;
    
    two_itemsets_trans_table = gen_two_itemsets_trans_table(one_minsup_item_counts_map, trans_vector);
          
    std::map<vector<int>, int> two_minsup_itemsets_counts_map = gen_n_minsups_itemsets_count_map(two_itemsets_trans_table, support_count);    
    std::map<vector<int>, int> L_final;
    std::map<vector<int>, int> L_minsup = two_minsup_itemsets_counts_map;
    std::map<int, vector<vector<int> > > prev_itemset_trans_table = two_itemsets_trans_table;
    
    myfile<<"Frequent 2 itemset size: "<<two_minsup_itemsets_counts_map.size()<<endl;
    myfile<<"Transaction Traverse Size: "<<prev_itemset_trans_table.size()<<endl;
    
    freq_itemset_counts.push_back(two_minsup_itemsets_counts_map.size());
    
    int count = 3;
    
    L_final = L_minsup;
    
    int start_s=clock();
	
    while(L_minsup.size() > 0){
        std::map<int, vector<vector<int> > > n_itemsets_trans_table;
        n_itemsets_trans_table = gen_n_itemsets_trans_table(L_minsup, prev_itemset_trans_table);
        
        L_minsup = gen_n_minsups_itemsets_count_map(n_itemsets_trans_table, support_count);
        prev_itemset_trans_table = n_itemsets_trans_table;
        
        myfile<<"Transaction Traverse Size: "<<n_itemsets_trans_table.size()<<endl;
        
        
        //if(L_minsup.size()>0){
            freq_itemset_counts.push_back(L_minsup.size());
            myfile<<"Frequent "<<count<<" itemset size: "<< L_minsup.size()<<endl;
        //}
        for (std::map<vector<int>,int>::iterator it=L_minsup.begin(); it!=L_minsup.end(); ++it){
            L_final[it->first] = it->second;  
        }
        count++;
    }   
    
    int stop_s=clock();
    myfile << "execution time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 <<" milliseconds"<< endl;
    
    if(c=="r"){
        gen_strong_association_rule(L_final, trans_vector.size(), one_minsup_item_counts_map, conf_threshold, c);
    }else if(c=="f"){
        print_map(one_minsup_item_counts_map, trans_vector.size());
        print_L_final(L_final, freq_itemset_counts.size(), trans_vector.size());
    }else if (c=="a"){
        gen_strong_association_rule(L_final, trans_vector.size(), one_minsup_item_counts_map, conf_threshold, c);
        print_map(one_minsup_item_counts_map, trans_vector.size());
        print_L_final(L_final, freq_itemset_counts.size(), trans_vector.size());
    } else if(c=="") {
        for(int i=0; i<freq_itemset_counts.size(); i++){
            cout<<"Number of frequent "<<i+1<<"_itemsets: "<<freq_itemset_counts[i]<<endl;
        }
        int count = gen_strong_association_rule(L_final, trans_vector.size(), one_minsup_item_counts_map, conf_threshold, c);
        cout<<"Number of strong association rules: "<<count<<endl;
    }
    
    myfile<<"Number of strong association rules: "<<gen_strong_association_rule(L_final, trans_vector.size(), one_minsup_item_counts_map, conf_threshold, "")<<endl;
    int total_freq_itemsets = L_final.size()+one_minsup_item_counts_map.size();
    myfile<<"Total frequent-itemset map size: "<<total_freq_itemsets<<endl;
//    myfile<<"Writing to file all frequent itemsets, and generating strong association rules (check current directory for the files."<<endl;
//    write_map(one_minsup_item_counts_map);    
//    write_L_final(L_final, count,trans_vector.size());
//    gen_strong_association_rule(L_final, trans_vector.size(), one_minsup_item_counts_map, conf_threshold);
    
    myfile<<"Processing Complete."<<endl;
    myfile.close();
    return 0;
}

int test_codes(){
    
    vector<int> dummy_itemset;
    dummy_itemset.push_back(1);
    dummy_itemset.push_back(2);
    dummy_itemset.push_back(3);
    dummy_itemset.push_back(4);
    dummy_itemset.push_back(5);
    dummy_itemset.push_back(6);
    dummy_itemset.push_back(7);
    dummy_itemset.push_back(8);
    dummy_itemset.push_back(9);
    dummy_itemset.push_back(10);
    dummy_itemset.push_back(11);
    
     
    vector<int> lt;  
    vector<vector<int> > vector_of_n_sub_items;
    subset(dummy_itemset,2,0,lt,vector_of_n_sub_items); 

    cout<<vector_of_n_sub_items.size()<<endl;
    return 0;
}

int main(int argc, char** argv) {
     
    if(argc < 4) {
        cout<<"You must provide minimum 3 arguments"<<endl;
        exit(0);
    }else if (argc >= 4 && argc < 5 ){
         string file_name = argv[1];
         double support =  strtod (argv[2], NULL);
         double confidence = strtod (argv[3], NULL);
         string c = "";
         freq_itemset_generator(file_name, support, confidence, c);
    }else if(argc >=5 && argc < 6){
         string file_name = argv[1];
         double support =  strtod (argv[2], NULL);
         double confidence = strtod (argv[3], NULL);
         string c = argv[4];
         freq_itemset_generator(file_name, support, confidence, c);
    }
    
    return 0;
}  


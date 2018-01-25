#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>

#include <stdlib.h>
#include <unistd.h>

#include "index_entry.h"
//#include "tree_class.h"
#include "cfn.h"
#include "comp.h"

#ifndef META_DATABASE_H
#define META_DATABASE_H

#define Buffer_Size 1000
#define i_min 15
#define q_min 1
#define q_max 20

#define dom_t 60

using namespace std;

class Meta_Result{
      
      public:
             
             friend class Meta_Database;
             
             Meta_Result(){
                        m_value =0;
                        entry = 0;   
                           
                           }
             Meta_Result(float _value, Index_Entry * _entry ){
                        m_value = _value;       
                        entry = _entry;       
                               }
      private:
              
             float m_value;
             Index_Entry * entry;
       
       };
       
class Meta_Database{
      
      public:
      
      Meta_Database(){
                      this->Entry_count = 0;
                      this->Entry_number = 0;
                      this->Key_dim = 0;
                      this->Name = "";   
                      this->Abundance = 0;    
                      //Comp_init();                                                           
                      }
      
      Meta_Database(string _name, int dim){
                      this->Entry_count = 0;
                      this->Entry_number = 0;
                      this->Key_dim = dim;
                      this->Name = _name; 
                      this->Abundance = 0;  
                      //Comp_init();    
                      }
                      
      Meta_Database(string _name, string path, int dim){
                           this->Entry_count = 0;
                           this->Entry_number = 0;
                           this->Key_dim = dim;
                           this->Name = _name; 
                           this->Abundance = 0;    
                           this->Make_Index(path);
                           //Comp_init();   
                           }
      Meta_Database(string infilename){
                           this->Entry_count = 0;
                           this->Entry_number = 0;
                           this->Abundance = 0;    
                           this->Load_Index(infilename);
                           //Comp_init();   
                           }
      ~Meta_Database(){};
      
      void Insert_Index_by_Entry(Index_Entry * entry);
      void Insert_Group_by_Entry(Index_Entry * entry);
      
      void Insert_Index_by_File(string infilename, unsigned int group);
      
      int Make_Index(string path);
      int Make_Index_Add(string path, unsigned int group);
      
      //unsigned int Query(string infilename);
      //unsigned int Exhaustive_Query(string infilename);
      unsigned int Parallel_Indexed_Query(ostream & out, string infilename, int n, int t_number, int group);
      unsigned int Parallel_Exhaustive_Query(ostream & out, string infilename, int n, int t_number, int group);
      
      int Out_Index(string outfilename);
      int Load_Index(string infilename);
      int Merge_Index(string infilename);
      
      int Get_Entry_Count(){ return this->Entry_count; };
      int Get_Key_Dim(){ return this->Key_dim; };
      int Get_Key_Count(){ return this->Meta_index.size(); };
      
      float Get_Abundance();
      float Update_Abundance();
      
    private:
              map<string, vector<Index_Entry * > * > Meta_index;
              map<unsigned int, vector<Index_Entry * > * > Meta_groups;
              unsigned int Entry_count;
              unsigned int Entry_number; //ID
              unsigned int Key_dim;
              string Name;
              
              //string Tree_file;
              
              int Abundance;
              //string Path;                            
              
              unsigned int Get_Entry_List(Index_Entry * * list, int group);
              unsigned int Get_Entry_List(Index_Entry * * list, string query_key, int group);
              
              unsigned int Parallel_Indexed_Query(string infilename, string query_key, Meta_Result * results, int n, int t_number, int group);
                            
              unsigned int Parallel_Query(string infilename, Index_Entry * * list, Meta_Result * results, int n, int t_number, int count);
              
              static void * Parallel_Query_Static(void * args);
                            
      };

struct Argument{
       
       string infilename;
       Index_Entry * * list;
       int thread;
       int per_number;
       int count;
       //string * tree_file;
       
       Meta_Result * buffer;

       };

#endif


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <math.h>

#ifndef INDEX_ENTRY_H
#define INDEX_ENTRY_H

#define delta 50

using namespace std;

class Index_Entry {
      
      public:
             Index_Entry(){
                          this->id = 0;
                          this->group = 0;
                          this->keys = NULL;
                          this->weight = NULL;
                          this->abundance = 0;
                          this->dim = 0;   
                          this->group = 0;                       
                          }

             Index_Entry(unsigned int _id, unsigned int _group, string * _keys, float * _weight, int _dim, string _filename, float d_min){
                             
                               this->id = _id;
                               this->group = _group;
                               this->dim = _dim;
                               this->keys = new string[_dim];
                               this->weight = new float[_dim];
                               
                               for (int i = 0; i < dim; i++){
                                   this->keys[i] = _keys[i];
                                   this->weight[i] = _weight[i];
                                   }
                               this->filename = _filename;
                               
                               this->abundance = this->Make_key(d_min);
                               
                               }
             
             Index_Entry(unsigned int _id, unsigned int _group, string key, int _dim, string _filename){
                                  
                                  this->id = _id;
                                  this->group = _group;
                                  this->key = key;
                                  this->dim = _dim;
                                  this->filename = _filename;
                                  
                                  this->abundance = 0;
             
                                  }
                               
             int Get_id(){
                          return this->id;
                 }
             
             int Get_group(){
                             return this->group;
                 }
             
             string Get_key(int i){
                    
                    if (i < this->dim) return this->keys[i];
                    else return "";
                    
                    }
                    
             string Get_key(){
                    
                    return this->key;
                    
                    }                    
             
             float Get_weight(int i){
                   
                   if (i < this->dim ) return this->weight[i];
                   else return 0;
             
                   }                                                
                          
             string Get_filename(){
                    
                    return this->filename;
                    
                    }
             
             float Get_abundance(){
                   
                   return this->abundance;
                   
                   }
             
      private:
              unsigned int id;
              unsigned int group;
              string * keys;
              float * weight;
              
              string key;
              float abundance;
              
              int dim;
              string filename;
                                          
              float Make_key(float d_min);   
      
      };

float Index_Entry :: Make_key(float d_min){
                    
                    string temp_keys[this->dim];
                    float temp_weight[this->dim];
                    
                    int key_count = 0;
                    float temp_abundance = 0;
                    
                    for (int i = 0; i < this->dim; i++){
                        if (this->weight[i] >= d_min){
                           temp_keys[i] = this->keys[i];
                           temp_weight[i] = this->weight[i];
                           key_count ++;
                           temp_abundance += this->weight[i];
                           }
                           
                        else break;
                        
                    }
                        
                   if (key_count == 0){
                             
                             this->key = "other";
                             return 0; 
                             } 
                    
                    for (int i = 0; i< key_count - 1; i++)
                        for (int j = i + 1; j < key_count; j++)
                            if ((temp_keys[i] > temp_keys[j])&&(abs(temp_weight[j] - temp_weight[i]) < delta)){
                                             
                                             string temp_k = temp_keys[i];
                                             temp_keys[i] = temp_keys[j];
                                             temp_keys[j] = temp_k;
                                             
                                             float temp_w = temp_weight[i];
                                             temp_weight[i] = temp_weight[j];
                                             temp_weight[j] = temp_w;
                                             
                                             }
                    
                    this->key = "";
                    
                    for (int i = 0; i < key_count; i++)
                        this->key += temp_keys[i];
                                       
                    
                    return temp_abundance; 
                    
                    }   
#endif


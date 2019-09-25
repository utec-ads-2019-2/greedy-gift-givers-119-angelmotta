#include <cstdio>
#include <vector>
#include <string>
#include <map>
using namespace std;

int c = 1;

void print_result(vector<string> name_list, map<string, int> &map_net_gain){
    //printf("-- Result -- \n");
    if(c > 1) printf("\n");
    for(auto name : name_list){
        auto itr = map_net_gain.find(name);
        printf("%s %d\n", name.c_str(), itr->second);
    }
    c++;
}

void update_others_net_gain(map<string, int> &map_net_gain, char name_others[15], int money, int num_gift_people){
    //printf("Update others net gain \n");
    auto itr = map_net_gain.find(name_others); 
    if( itr != map_net_gain.end()){ // key already exist
        //printf("Update key: %s - Value: %d \n", itr->first.c_str(), itr->second + (money/num_gift_people));
        map_net_gain[itr->first] = itr->second + (money/num_gift_people); // Update its existing value
    }
    else{
        //printf("Insert key: %s - Value: %d \n", name_others, (money/num_gift_people));
        map_net_gain.insert({name_others, (money/num_gift_people)});
    }
}

void update_personal_net_gain(map<string, int> &map_net_gain, char name[15], int money, int num_gift_people){
    //printf("Update personal net gain \n");
    auto itr = map_net_gain.find(name);
    if( itr != map_net_gain.end()){ // key already exist
        if(num_gift_people == 0){
            //printf("Updating key: %s - value: %d\n", itr->first.c_str(), itr->second + money);
            //if(num_gift_people > 0) map_net_gain[itr->first] = itr->second + money; // Update its existing value - Resta
            return;    
        }
        else{
            //printf("Updating key: %s - value: %d\n", itr->first.c_str(), itr->second - (money/num_gift_people));
            if(num_gift_people > 0) map_net_gain[itr->first] = itr->second - (money/num_gift_people)*num_gift_people; // Update its existing value - Resta
        }
    }
    else{   // If not exist in the map
        if(num_gift_people == 0){
            //result = money - result;
            //printf("Insert key: %s - value: %d\n", name, money);
            map_net_gain.insert({name, 0});
        }    
        else if(num_gift_people > 0){
            //printf("Not exist...Insert key: %s value: %d\n", name, -(money/num_gift_people)*num_gift_people);
            map_net_gain.insert({name, -(money/num_gift_people)*num_gift_people});
        }
    }
    // first logic
    /*if(num_gift_people == 0){
        //result = money - result;
        map_net_gain.insert({name, money});
    }
    else{
        result = money/num_gift_people;
        result = money - result;
        //printf("Restas: %d \n", result);
        map_net_gain.insert({name, result});
    }*/
}

int main(){
    int number_people = 0;
    char name[15], name_others[15];
    int money, num_gift_people;
    while(scanf("%d", &number_people) != EOF ){
        vector<string> name_list;
        map<string, int> map_net_gain {};
        for(int i=0; i<number_people; ++i){
            scanf("%s", name);
            //printf("Ingresaste: %s \n",name);
            name_list.push_back(name);
        }
        for(int i=0; i<number_people; ++i){
            scanf("%s %d %d", name, &money, &num_gift_people);
            update_personal_net_gain(map_net_gain, name, money, num_gift_people);
            for(int i=0; i<num_gift_people; ++i){
                scanf("%s", name_others);
                //printf("Ingresaste others: %s \n",name_others);
                update_others_net_gain(map_net_gain, name_others, money, num_gift_people);
            }
        }
        print_result(name_list, map_net_gain);
    }
    return 0;
}
#include <iostream>
using namespace std;
void sprite(){
    cout <<"                             /\\                        /\\"<<endl;
    cout <<"                            /||\\                      /||\\"<<endl;
    cout <<"                        ___/||||\\____________________/||||\\_____"<<endl;
    cout <<"                       /########################################\\"<<endl;
    cout <<"                      /######\\\\##########################//######\\"<<endl;
    cout <<"                      \\#######\\\\########################//#######/"<<endl;
    cout <<"                       \\#######\\\\######################//#######/"<<endl;
    cout <<"                        \\######################################/"<<endl;
    cout <<"                         \\####     ##################     ####/"<<endl;
    cout <<"                          \\### ||| ################## ||| ###/"<<endl;
    cout <<"                           \\## ||| ################## ||| ##/"<<endl;
    cout <<"                            \\##############################/      "<<endl;
    cout <<"                           /#\\############################/#\\"<<endl;
    cout <<"                          |###\\##########################/###|"<<endl;
    cout <<"                         /|####\\########################/####|\\"<<endl;
    cout <<"                        /#|#####\\######################/#####|#\\"<<endl;
    cout <<"                       /##|######\\|||||||||VV|||||||||/######|##\\"<<endl;
    cout <<"                      /###|###################################|###\\"<<endl;
    cout <<"                     /####|###################################|####\\"<<endl;
}
struct stats
{
    int life;
    int attack;
    int defense;
    int critticpercentage;
};
struct enemystats{
    int enemylife;
    int enemydamage;
    int enemydefense;
};
int stat(int d){
    stats statsdificulty;
    if (d >= 0 || d <= 3)
    {
        switch (d)
    {
    case 1:
        statsdificulty.life = 150;
        statsdificulty.attack=45;
        statsdificulty.defense = 40;
        statsdificulty.critticpercentage = 1;
        break;
    case 2:
        statsdificulty.life = 200;
        statsdificulty.attack = 60;
        statsdificulty.defense = 45;
        statsdificulty.critticpercentage = 5;
        break;
    case 3:
        statsdificulty.life = 260;
        statsdificulty.attack = 70;
        statsdificulty.defense = 50;
        statsdificulty.critticpercentage = 10;
        break;
    default:
        break;
    }
    }
    
    
}
int main() {
    int difficulty;
    cin >> difficulty;
    switch (difficulty)
    {
    case 1:
        stat(difficulty);
        cout <<"|===================================|"<<endl;
        cout <<"| So, you finally came to my lair...|"<<endl;
        cout <<"|===================================|"<<endl;
        cout <<""<<endl;
        sprite();
        break;
    case 2:
        cout <<"|===================================|"<<endl;
        cout <<"| So, you finally came to my lair...|"<<endl;
        cout <<"|===================================|"<<endl;
        break;
    case 3:
        cout <<"|===================================|"<<endl;
        cout <<"| So, you finally came to my lair...|"<<endl;
        cout <<"|===================================|"<<endl;
        break;
    
    default:
        break;
    }
    
    }
    
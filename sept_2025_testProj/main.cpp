#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<random>
#include<ctime> //quick solution to seed rand without needing to spend time
#include<vector>
//test change
//Small note, it would be very very funny if I got my cpp program to interface with the rust rand proj
#define COL_SIZE 8
#define ROW_SIZE 8
/*
Small note on being a super lazy person with regards to this sillyness
I can have three separate text files in my assets folder or something like that, 
then I can load in the different categories of question into my program memory and then use them when I see fit, 
(I can have a simple read line and then have one question per line in the txt file
also, it doesn't need to be a txt file)
I can also be silly and then load in batches and then clear my 'buffer' and reload when I deplete the batch
so that I don't load too many questions into my memory but then again I don't think that this makes too too much sense at the moment, wiill leave this pondering thing here anyway*/

class pObj{
private:
  //score and position for now, not sure if I need anything else 
  int pID = 0;// this is the player id, should be unique 
  int score = 0; //probably better to be a uint
  int pos[2] = { 0,0 }; // row,col
  char name[32] = "unNamed"; //32 character limit for the player name
  int qAnsCnt = 0; //this is the number of questions that they have gotten,
public:
  pObj(int id)
  {
    //set pID for the object
    pID = id;
    std::cout << "Player " << id << " created..." << std::endl;
  }
  void initName() 
  {
    std::cout << "PlayerName = ";
    std::cin >> name;
    std::cout << std::endl << "Thank you " << "\t" << name << std::endl;
    return;
  }
  void updatePos(int moveNum) 
  {
    //need to see how many lines to move down
    //also, am only moving forward in this version of the game as I need it working by saturday morning I should have really started this earlier
    pos[0] = pos[0] + ((pos[1]+ moveNum) / COL_SIZE); // e.g if I am on row 0 col 7, and I need to move forward by 2, then I want to move to row 1 col 1
    pos[1] = ((pos[1] + moveNum) % COL_SIZE);
  }

  void dispPos() 
  {
    std::cout << name << " = " << "\t" << "row = " << pos[0] << "\t" << "col = " << pos[1] << std::endl;
    return;
  }
};

class qPool {
private:

  std::vector<std::string> question[4];
  //std::vector<int[32]> kf; 
  //I think for now, it would be nice to remove the question when it is used.
  int qCnt[4] = { 0,0,0,0 }; //keep count of questions remaining and whatnot for when popping

public:
  void printQuestions()
  {
    //FOR DEBUGGING mainly
    std::string qDiff[4] = { "easy","medium","hard","used" };
    int tempSize = 0;
    for (int i = 0; i < 4; i++) {
      std::cout << "\n \n" << qDiff[i] << ": " << qCnt[i] << " QUESTIONS" << "\n";
      for (int j = 0; j < qCnt[i]; j++) {
        std::cout << "QUESTION " << j + 1 << " = " << question[i][j] << "\n";
      }
      std::cout << "FINISHED PRINTING (" << qDiff[i] << ")" << "\n";
    }
    return;
  }
  void load() 
  {
    //load questions in on making the object
    //load easy
    ///char temp[1024];
    std::string tempS;
    int cCnt;
    std::string fName[4] = { "easy.txt","medium.txt","hard.txt","used.txt" };
    for (int i = 0; i < 4; i++) {

      std::fstream f(fName[i]);
      //f.open("easy.txt","rb");
      if (f.is_open()) {
        while (!f.eof())
        {
          cCnt = 0;
          std::getline(f, tempS);

          question[i].push_back(tempS);
          qCnt[i] += 1;
        }
        std::cout << "loaded in " << qCnt[i] << fName[i] << "  questions... " << std::endl;
        f.close();
      }
      else {
        std::cout << fName[i] << "  NOT FOUND" << "\n";
        f.close();
      }
    }
    
    printQuestions();
    return;
  }
  void useQuestion(int diff) 
  {
    return;
  }
};
void displayGameStatus(std::vector<pObj*> players, int numPlayers, int turnNum)
{
  //Display game information each round
  //e.g. player positions and the score (number of questions, perhaps number of questions answered correctly)
  std::cout << "\t \t" << "TURN " << turnNum << " STATUS: \n";
  //Position display
  for (int i = 0; i < numPlayers; i++) {
    players[i]->dispPos();
  }

  return;
}
void initGamePlayers(std::vector<pObj*> players, int numPlayers)
{
  //Get the player names for all of the players that are playing
  //Also, display the current player positions
}
int game(std::vector<pObj>* players, int numPlayers, qPool* questions) 
{
  //I want to directly modify the variables in memory (actually do I really want to?)
  /*
  General program loop would be,
  I have the player turn order (to have been decided in the creation of the player IDs*/
  return 0;
}
int main() {
  int numPlayers = 0; 
  std::cout << "Enter a number << ";
  std::cin >> numPlayers;
  std::vector<pObj*> players;
  for (int i = 1; i <= numPlayers; i++) {
    players.push_back(new pObj(i));
  }
  displayGameStatus(players, numPlayers, 3);
   
  displayGameStatus(players, numPlayers, 4);

  qPool q;
  q.load();
  /*pObj* newGuy = new pObj(45);
  newGuy->initName();
  newGuy->dispPos();
  newGuy->updatePos(7); 
  newGuy->dispPos();
  newGuy->updatePos(2);
  newGuy->dispPos();
  */
  return 0;
}
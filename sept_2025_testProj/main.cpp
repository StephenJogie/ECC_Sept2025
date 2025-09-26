#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<cstdlib>
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
  std::string name = "unName"; //32 character limit for the player name
  int qAnsCnt = 0; //this is the number of questions that they have gotten,
public:
  bool didWin() {
    return (pos[0] >= ROW_SIZE);
  }
  pObj(int id)
  {
    //set pID for the object
    pID = id;
    std::cout << "Player " << id << " created..." << std::endl;
  }
  void initName() 
  {
    std::cout << "Player " << pID << " Name = ";
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

  std::string retName() {
    return name;
  }
  void updateScore(bool isCorrect)
  {
    score += isCorrect; 
    qAnsCnt += 1;;
  }
};

class qPool {
private:

  std::vector<std::string> question[4];
  //std::vector<int[32]> kf; 
  //I think for now, it would be nice to remove the question when it is used.
  int qCnt[4] = { 0,0,0,0 }; //keep count of questions remaining and whatnot for when popping

public:
  std::string useQuestion(int qDiff)
  {
    int qInd = rand() % (qCnt[qDiff]);
    
    if (qCnt[qDiff] >= 1)
    {
      std::cout << "QUESTION: " << "\n \n \n \n";
      std::cout << question[qDiff][qInd] << "\n" << "\n";
      question[3].push_back(question[qDiff][qInd]);
      question[qDiff][qInd].pop_back();
      qCnt[qDiff] -= 1;
      qCnt[3] += 1;
      return(question[3][qCnt[3] - 1]);
    }
    else {
      //depleted the questions, need to make up on the spot but the game must continue
      std::cout << "QUESTION: " << "\n \n \n \n";
      std::cout << "OUT OF QUESTIONS!!! GAMEMASTER PLEASE DO SOMETHING!!!!" << "\n" << "\n";
      return("OUT OF QUESTIONS!!! GAMEMASTER PLEASE DO SOMETHING!!!!");
    }
   
    
    
  }
  void printQuestions()
  {
    //FOR DEBUGGING mainly
    std::string qDiff[4] = {"easy","medium","hard","used"};
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
    std::string fName[4] = {"easy.txt","medium.txt","hard.txt","used.txt"};
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
  
};
int rollDice() {
  //I would like to automate it but unfortunately I think that the target audience would rather roll real dice
  //prompt to input the value.
  //I am trusting that it is a valid input
  std::cout << "WHAT VALUE DID YOU ROLL: ";
  int retVal = 0;
  std::cin >> retVal;
  std::cout << "UNDERSTOOD ... " << retVal << "..." << std::endl;
  return retVal;
}
void playQuestion(pObj* player, int numPlayers, qPool* q, int qDiff)
{
  //FOR THIS VERSION ONLY EASY
  

  bool val = 0;
  int moveVal = rollDice();
  q->useQuestion(qDiff); // difficulty easy
  while (!val) {
    std::cout << "Did " << player->retName() << " answer correctly ( y(1) / n(0) ) :";
    int temp;
    std::cin >> temp;
    
    
    if (temp != 1 && temp != 0)
    {
      std::cout << "INVALID ENTRY" << "\n";
    }
    else {
      // I want to add to the player score
      player->updateScore(temp);
      player->updatePos(moveVal * temp);
      val = true;
    }
    player->dispPos();
  }

  return;
}
void displayGameStatus(std::vector<pObj*> players, int numPlayers, int turnNum)
{
  //Display game information each round
  //e.g. player positions and the score (number of questions, perhaps number of questions answered correctly)
  std::cout << "\t \t" << " END OF TURN " << turnNum << " STATUS: \n";
  //Position display
  for (int i = 0; i < numPlayers; i++) {
    std::cout << "\t" << players[i]->retName() << std::endl; 

    players[i]->dispPos();
  }

  return;
}
void initGamePlayers(std::vector<pObj*> players, int numPlayers)
{
  //Get the player names for all of the players that are playing
  //Also, display the current player positions
  for (int i = 0; i < numPlayers; i++) {
    players[i]->initName();
  }
}
void game(std::vector<pObj*> players, int numPlayers, qPool* questions) 
{
  //I want to directly modify the variables in memory (actually do I really want to?)
  /*
  General program loop would be,
  I have the player turn order (to have been decided in the creation of the player IDs*/
  /*
  * Game loop is as follows 
  * For each 'turn', all players play one question. 
  * At the end of the turn I would be displaying the current 'state' of the game
  * Before the turn ends and it loops into another turn, I would see if anyone 'won' the game
  * (actually, better to break the loop as soon as someone wins)
  * Keep looping turns until there is a winner
  * When the game is won, I would need to display the winner
  */
  initGamePlayers(players, numPlayers);
  
  bool done = 0; 
  int turn = 0;
  std::string tempS;
  while (!done)
  {
    turn += 1;
    std::cout << "==========================" << std::endl;
    std::cout << "Turn " << turn << "::::: " << std::endl;
    for (int i = 0; i < numPlayers; i++)
    {
      tempS = players[i]->retName();
      std::cout << "\t" << tempS << "'s TURN START" << "\n";
      playQuestion(players[i], numPlayers, questions, 1);
      if (players[i]->didWin()) {
        std::cout << "WINNER" << std::endl;
        done = 1;
        break;
      }
      std::cout << "\t" << tempS << "'s TURN END" << "\n";
    }
    displayGameStatus(players, numPlayers, turn);
  }
  return;
}

int main() {
  srand(time(NULL)); //seed with time
  int numPlayers = 0; 
  std::cout << "Enter a number << ";
  std::cin >> numPlayers;
  std::vector<pObj*> players;
  for (int i = 1; i <= numPlayers; i++) {
    players.push_back(new pObj(i));
  }
  //displayGameStatus(players, numPlayers, 3);
   
  //displayGameStatus(players, numPlayers, 4);

  qPool q;
  q.load();
  //playQuestion(players[0], numPlayers, &q, 0);
  /*pObj* newGuy = new pObj(45);
  newGuy->initName();
  newGuy->dispPos();
  newGuy->updatePos(7); 
  newGuy->dispPos();
  newGuy->updatePos(2);
  newGuy->dispPos();
  */
  game(players, numPlayers, &q);
  return 0;
}
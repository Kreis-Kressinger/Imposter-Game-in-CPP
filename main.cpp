// Using GNU General Public License 2.0 or later


#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>
#include <ctime>
#include <fstream>

std::string turnLowerCase(std::string str) {
    for (char& ch : str) {
	ch = std::tolower(ch);
    }
    return str;
}

class player {

    bool imposter;
    std::string word;
    std::string name;
    std::string typedWord;
    bool isOut = false;

    public:

    player(bool isImposter, std::string word, std::string name) {
	this->imposter = isImposter;
	this->word = word;
	this->name = name;
    }

    bool isImposter() {
	return this->imposter;
    }

    void setIsOut(){
	this->isOut = true;
    }

    bool getIsOut(){
	return this->isOut;
    }

    std::string getName() {
	return this->name;
    }

    void setTypedWord(std::string typedWord) {
	this->typedWord = typedWord;
    }

    std::string getTypedWord() {
	return this->typedWord;
    }

    bool checkGuess() {
	if (turnLowerCase(this->typedWord) == turnLowerCase(this->word)) {
	    return true;
	}
	return false;
    }
};

void spamNewLine(){
    for(int i = 0; i < 60; i++){
	std::cout << '\n';
    }
}


int playerNum;
int imposterNum;

bool game() {

    int lineNum = 1;
    std::string line;

    std::vector<std::string> wordList;
    std::vector<std::string> hintList;

    std::ifstream file("wordSet.txt");
    if(!file.is_open()){
	std::cout << "wordSet.txt konnte nicht geöffnet.";
	return false;
    }

    while(std::getline(file,line)){

	if(lineNum % 2 == 1){
	    wordList.push_back(line);
	}else{
	    hintList.push_back(line);
	}


	lineNum++;
    }    






    srand(time(0));
    std::cout << "Wie viele Spieler (max 10, min 3): ";

    while (!(std::cin >> playerNum) || playerNum > 10 || playerNum < 3) {
	std::cout << "Wie viele Spieler (max 10, min 3): ";
	std::cin.clear();
	std::cin.ignore(10000, '\n');
    }

    std::cout << "Wie viele Imposter (max 4, min 1, und dürfen nicht 50% der Spieler oder mehr sein): ";

    while (!(std::cin >> imposterNum) || imposterNum > 4 || imposterNum < 1 || imposterNum >= static_cast<double>(playerNum) / 2) {
	std::cout << "Wie viele Imposter (max 4, min 1, und dürfen nicht 50% der Spieler oder mehr sein): ";
	std::cin.clear();
	std::cin.ignore(10000, '\n');
    }

    std::vector<player> listOfPlayers;
    std::vector<bool> imposterList(playerNum, false);

    int chosenImposters = 0;

    while (chosenImposters < imposterNum) {
	int tempImposter = rand() % playerNum;

	if (!imposterList.at(tempImposter)) {
	    chosenImposters++;
	    imposterList.at(tempImposter) = true;
	}
    }
    srand(time(0));
    int randomWordIndex = rand() % (wordList.size());
    std::string chosenWord = wordList.at(randomWordIndex);

    for (int i = 0; i < playerNum; i++) {

	std::string tempName;

	std::cout << "Spieler(" << i + 1 << ") gib deinen Namen ein: ";
	std::cin >> tempName;

	player tempPlayer(imposterList.at(i), chosenWord, tempName);
	listOfPlayers.push_back(tempPlayer);
    }

    int round = 0;

    while (true) {

	for (player& p : listOfPlayers) {

	    if(p.getIsOut()){
		continue;
	    }

	    std::string tempWord;
	    spamNewLine();
	    std::cout << "Du bist dran: " << p.getName() << '\n';
	    std::cout << "Druecke Enter...";  
	    std::cin.ignore(10000, '\n');
	    std::cin.get();
	    if (p.isImposter()) {

		std::cout << "Du bist Imposter. Der Hinweis lautet: "
		    << hintList.at(randomWordIndex)
		    << '\n'
		    << "Versuche das richtige Wort zu raten ohne dass du auffaelig bist: ";

		std::cin >> tempWord;
		p.setTypedWord(tempWord);

		if (p.checkGuess()) {
		    std::cout << '\n' << '\n'
			<< "*****************" << '\n'
			<< p.getName() << " gewinnt, weil er/sie/es das richtige Wort erraten hat! Das Wort war: "
			<< tempWord << '\n'
			<< "*****************" << '\n';
		    for(int i = 0; i < listOfPlayers.size(); i++){
			listOfPlayers.pop_back();
		    }
		    char tempchar;
		    std::cout << "Wollt ihr noch eine Runde Spielen? (Y/N): ";
		    std::cin >> tempchar;
		    if(tolower(tempchar) == 'y'){
			return true;
		    }
		    return false;
		}

	    } else {

		std::cout << "Du bist kein Imposter. Das Wort lautet: "
		    << wordList.at(randomWordIndex)
		    << '\n'
		    << "Versuche ein aehnliches Wort zu sagen, damit die anderen dir glauben, dass du kein Imposter bist: ";

		std::cin >> tempWord;	
		p.setTypedWord(tempWord);
	    }
	}

	std::cout << '\n' << "Eingegebene Woerter:" << '\n';

	for (player& p : listOfPlayers) {
	    std::cout << p.getName() << ": " << p.getTypedWord() << '\n';
	}

	std::cout << '\n'
	    << "Wollt ihr jetzt versuchen einen Imposter rauszuwaehlen oder zur Sicherheit noch eine Runde machen? (Y/N) ";
	char choice;
	while(!(std::cin >> choice) || toupper(choice) != 'Y' && toupper(choice) != 'N'){
	    std::cin.clear();
	    std::cin.ignore(10000, '\n');
	}

	if(toupper(choice) == 'Y'){

	    int kickChoice;

	    for(int i = 0; i < listOfPlayers.size(); i++){

		std::cout << i+1 << ": " << listOfPlayers[i].getName() << '\n';

	    }

	    std::cout << "Waehle eine Nummer um den jeweiligen Spieler zu kicken: ";
	    std::cin >> kickChoice;
	    listOfPlayers[kickChoice-1].setIsOut();

	    bool allImpostersGone = true;
	    int imposterNumba = 0;
	    int innocentNumba = 0;
	    for(player p : listOfPlayers){

		if(p.getIsOut()){
		    continue;
		}
		if(p.isImposter()){
		    allImpostersGone = false;
		    imposterNumba++;
		}else{
		    innocentNumba++;	
		}


		if(innocentNumba <= imposterNumba){
		    std::cout << '\n' << "****************************" << '\n' << "Die Imposter gewinnen, weil sie nun 50% der Spieler oder mehr sind." << '\n' << "****************************" << '\n';
		    for(int i = 0; i < listOfPlayers.size(); i++){
			listOfPlayers.pop_back();
		    }
		    char tempchar;
		    std::cout << '\n' << "Wollt ihr noch eine Runde Spielen? (Y/N): ";
		    std::cin >> tempchar;
		    if(tolower(tempchar) == 'y'){
			return true;
		    }
		    return false;


		}	
	    }
	    if(allImpostersGone){
		std::cout << "****************************" << '\n' << "Alle Imposter wurden gefasst. Die Anderen gewinnen!" << '\n' << "****************************";
		for(int i = 0; i < listOfPlayers.size(); i++){
		    listOfPlayers.pop_back();
		}
		char tempchar;
		std::cout << "Wollt ihr noch eine Runde Spielen? (Y/N): ";
		std::cin >> tempchar;
		if(tolower(tempchar) == 'y'){
		    return true;
		}
		return false;

	    }
	}else{
	    continue;
	}

    }

}

int main(){
    std::cout 
	<< '\n' << "************************"
	<< '\n'
	<< "Willkommen bei Imposter!"
	<< '\n'
	<< "************************"
	<< '\n'
	<< '\n';
    while(game()){
    }

    return 0;
}


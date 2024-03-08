#include "Engine.h"

// Called once at the start
bool Engine::OnUserCreate()
{
	//seed rand
	srand(time(NULL));
	
	//create default queues
	//express
	expressQs.push_back(new Queue(1, this->fTargetTime));
	expressQs.push_back(new Queue(1, this->fTargetTime));
	
	//normal
	normalQs.push_back(new Queue(0, this->fTargetTime));
	normalQs.push_back(new Queue(0, this->fTargetTime));

	return true;
}

//called once per frame
bool Engine::OnUserUpdate(float fElapsedTime)
{

	/*time managment (sets time before frame change) 
	speed can be increased by decreasing target time
	entire frame logic is wrapped in if statement*/

	fAccumulatedTime += fElapsedTime;

	if (fAccumulatedTime >= fTargetTime) {
		fAccumulatedTime -= fTargetTime;
		fElapsedTime = fTargetTime;

		/*SIMULATION*/

		//check for enqueue/dequeue events
		//normal
		for (int i = 0; i < normalQs.size(); i++) {
			//enqueue
			if (normalQs[i]->checkEnQTime()) {
				normalQs[i]->enqueue();
				const Data temp = normalQs[i]->getTail()->getData();
				cout << "Q" << i << ":Normal:" << "Enqueue:" << "ID:" << temp.getID() << "wTime" << temp.getTime() << endl;
				normalQs[i]->resetEnq();
			}
			else {
				normalQs[i]->decEnQTime(fElapsedTime);
			}
			//dequeue
			//check only if nodes are queued
			if (normalQs[i]->checkDecQTime()) {
				Data temp = normalQs[i]->dequeue();
				cout << "Q" << i << ":Normal:" << "Dequeue:" <<"Total Time:" << temp.getTotal() << endl;
			}
			else {
				if (normalQs[i]->isEmpty() == false) {
					normalQs[i]->decDecQTime(fElapsedTime);
				}
			}
		}
		//express
		for (int i = 0; i < expressQs.size(); i++) {
			//enqueue
			if (expressQs[i]->checkEnQTime()) {
				expressQs[i]->enqueue();
				const Data temp = expressQs[i]->getTail()->getData();
				cout << "Q" << i << ":Express:" << "Enqueue:" << "ID:" << temp.getID() << "wTime" << temp.getTime() << endl;
				expressQs[i]->resetEnq();
			}
			else {
				expressQs[i]->decEnQTime(fElapsedTime);
			}
			//dequeue
			if (expressQs[i]->checkDecQTime()) {
				Data temp = expressQs[i]->dequeue();
				cout << "Q" << i << ":Express:" << "Dequeue:" << "Total Time:" << temp.getTotal() << endl;
			}
			else {
				if (expressQs[i]->isEmpty() == false) {
					expressQs[i]->decDecQTime(fElapsedTime);
				}
				
			}
		}

		/*DRAWING*/

		//clear screen
		Clear(olc::BLACK);

		//queue box width/height
		int qDWidth = ScreenWidth() - 12;
		int qDHeight = ScreenHeight() / expressQs.size() - 12;
		//customer box width/height
		int cDWidth = (ScreenWidth() - 13); //need to divide by # of members in each queue
		int cDHeight = (ScreenHeight() / expressQs.size() - 13)/2;

		//temp for retrieve data from nodes
		QueueNode* temp;

		//draw border
		DrawRect(BORDER_WIDTH, BORDER_WIDTH, ScreenWidth() - (BORDER_WIDTH * 2), ScreenHeight() - (BORDER_WIDTH * 2), olc::RED);

		//draw queue boxes
		for (int i = 0; i < expressQs.size(); i++) {
			DrawRect(6, (ScreenHeight() / expressQs.size()) * i + 6, ScreenWidth() - 12, ScreenHeight() / expressQs.size() - 12, olc::BLUE);
			
			//draw express
			temp = expressQs[i]->getHead();

			for (int j = 0; j < expressQs[i]->queueSize(); j++) {

				if (expressQs[i]->queueSize() != 0 && temp != nullptr) {
					//draw nodes
					///                      x                           ,                      y                      ,        w                            ,     h
					FillRect(((1 + (cDWidth / expressQs[i]->queueSize())) * j) + 8, (ScreenHeight() / expressQs.size() * i) + 7 , (cDWidth / expressQs[i]->queueSize()) - 6, cDHeight, temp->getColor());
					//draw ID text
					DrawString(((1 + (cDWidth / expressQs[i]->queueSize())) * j) + 12, (ScreenHeight() / expressQs.size() * i) + 12, std::to_string(temp->getData().getID()), olc::BLACK, 1);

					temp = temp->getNext();
				}
				
			}
			//draw regular
			temp = normalQs[i]->getHead();

			for (int j = 0; j < normalQs[i]->queueSize(); j++) {
				if (normalQs[i]->queueSize() != 0 && temp != nullptr) {
					//draw nodes
					///                      x                           ,                      y                      ,        w                            ,     h
					FillRect(((1 + (cDWidth / normalQs[i]->queueSize())) * j) + 8, ((ScreenHeight() / normalQs.size() * i) + 7) + cDHeight, (cDWidth / normalQs[i]->queueSize()) - 6, cDHeight, temp->getColor());
					//draw ID text
					DrawString(((1 + (cDWidth / normalQs[i]->queueSize())) * j) + 12, ((ScreenHeight() / normalQs.size() * i) + 12) + cDHeight, std::to_string(temp->getData().getID()), olc::BLACK, 1);
					
					temp = temp->getNext();
				}

			}
			//draw current wait time text
			DrawString(6, (ScreenHeight() / expressQs.size())* i + 6, std::to_string(expressQs[i]->getWait()), olc::CYAN);
			DrawString(6, (ScreenHeight() / expressQs.size())* i + cDHeight, std::to_string(normalQs[i]->getWait()), olc::CYAN);
			
		}

		//end frame time if
	}

	/*user input*/
	//console activate on f1
	if (GetKey(olc::Key::F1).bPressed) {
		ConsoleShow(olc::Key::ESCAPE);
	}

	return true;
}

//handle console input
//TODO: type and error checking
bool Engine::OnConsoleCommand(const std::string& sText) {
	std::stringstream buff;
	buff << sText;

	std::string c1;
	buff >> c1;

	if (c1 == "add") {
		
		int n = 0;
		buff >> n;

		for (int i = 0; i < n; i++) {
			Queue* eTemp = new Queue(1, this->fTargetTime);
			Queue* nTemp = new Queue(1, this->fTargetTime);
			expressQs.push_back(eTemp);
			normalQs.push_back(nTemp);
		}
		cout << "Adding " << n << " queues" << endl;
	}else if (c1 == "remove") {

		int n = 0;
		buff >> n;

		for (int i = 0; i < n; i++) {
			expressQs.pop_back();
			normalQs.pop_back();
		}
		cout << "removing " << n << " queues" << endl;
	}
	else if (c1 == "speed") {
		
		float n = 1.0;
		buff >> n;

		fTargetTime *= n;
	}

	return true;

}
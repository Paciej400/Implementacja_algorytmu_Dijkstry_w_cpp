#include <iostream>
using namespace std;
#define EXTRAMINUTE 1

struct Point {
	int x;
	int y;
};

struct Lift {
	struct Point stPoint;
	struct Point endPoint;
	int duration;
	int departure;
};

struct State {
	int width;
	int height;
	int numberOfLifts;
	Lift* lifts;
	struct Point startingPoint;
	struct Point endingPoint;
	int** tableOfHeightValues;
	int** tableOfTime;
};

class QueueNode {
public:
	struct Point data;
	int time;
	QueueNode* next;
	QueueNode(struct Point p, int time)
		:data(p), time(time), next(nullptr)
	{
	}
	void addNext(QueueNode* next) {
		this->next = next;
	}
};

class Queue {
private:
	QueueNode* first;
	QueueNode* last;
public:
	Queue()
		: first(nullptr), last(nullptr)
	{
	}
	void push(struct Point p, State* state) {
		int timeAtATile = state->tableOfTime[p.y][p.x];
		if (first == nullptr) {
			first = new QueueNode(p, timeAtATile);
			last = first;
		}
		else {
			QueueNode* toBeAdded = new QueueNode(p, timeAtATile);
			QueueNode* current = first;
			while (current != last && current->next != last) {
				if (timeAtATile < current->next->time) {
					toBeAdded->addNext(current->next);
					current->addNext(toBeAdded);
					break;
				}
				current = current->next;
			}
			if (current == last || current->next == last) {
				last->addNext(toBeAdded);
				last = last->next;
			}
		}
	}
	struct Point pop() {
		if (first == nullptr) {
			struct Point p = { 0, 0 };
			return p;
		}
		else if (first == last) {
			struct Point temp = first->data;
			delete first;
			first = nullptr;
			last = nullptr;
			return temp;
		}
		struct Point temp = first->data;
		QueueNode* tempFirst = first->next;
		delete first;
		first = tempFirst;
		return temp;
	}
	bool isEmpty() {
		return first == nullptr;
	}
};

void upCondition(State* state, Queue* uncheckedVertices, struct Point currentVertex) {
	if (currentVertex.y != 0 && state->tableOfHeightValues[currentVertex.y][currentVertex.x] >=
		state->tableOfHeightValues[currentVertex.y - 1][currentVertex.x]) {
		int newTime = state->tableOfTime[currentVertex.y][currentVertex.x] + EXTRAMINUTE;
		if (state->tableOfTime[currentVertex.y - 1][currentVertex.x] > newTime &&
			newTime < state->tableOfTime[state->endingPoint.y][state->endingPoint.x]) {
			state->tableOfTime[currentVertex.y - 1][currentVertex.x] = newTime;
			struct Point vertexToBeChecked = { currentVertex.x, currentVertex.y - 1 };
			uncheckedVertices->push(vertexToBeChecked, state);
		}
	}
	else if (currentVertex.y != 0) {
		int heightDifference = state->tableOfHeightValues[currentVertex.y - 1][currentVertex.x] -
			state->tableOfHeightValues[currentVertex.y][currentVertex.x];
		int newTime = state->tableOfTime[currentVertex.y][currentVertex.x] + heightDifference + EXTRAMINUTE;
		if (state->tableOfTime[currentVertex.y - 1][currentVertex.x] > newTime &&
			newTime < state->tableOfTime[state->endingPoint.y][state->endingPoint.x]) {
			state->tableOfTime[currentVertex.y - 1][currentVertex.x] = newTime;
			struct Point vertexToBeChecked = { currentVertex.x, currentVertex.y - 1 };
			uncheckedVertices->push(vertexToBeChecked, state);
		}
	}
}

void downCondition(State* state, Queue* uncheckedVertices, struct Point currentVertex) {
	if (currentVertex.y != state->height - 1 && state->tableOfHeightValues[currentVertex.y][currentVertex.x] >=
		state->tableOfHeightValues[currentVertex.y + 1][currentVertex.x]) {
		int newTime = state->tableOfTime[currentVertex.y][currentVertex.x] + EXTRAMINUTE;
		if (state->tableOfTime[currentVertex.y + 1][currentVertex.x] > newTime &&
			newTime < state->tableOfTime[state->endingPoint.y][state->endingPoint.x]) {
			state->tableOfTime[currentVertex.y + 1][currentVertex.x] = newTime;
			struct Point vertexToBeChecked = { currentVertex.x, currentVertex.y + 1 };
			uncheckedVertices->push(vertexToBeChecked, state);
		}
	}
	else if (currentVertex.y != state->height - 1) {
		int heightDifference = state->tableOfHeightValues[currentVertex.y + 1][currentVertex.x] -
			state->tableOfHeightValues[currentVertex.y][currentVertex.x];
		int newTime = state->tableOfTime[currentVertex.y][currentVertex.x] + heightDifference + EXTRAMINUTE;
		if (state->tableOfTime[currentVertex.y + 1][currentVertex.x] > newTime &&
			newTime < state->tableOfTime[state->endingPoint.y][state->endingPoint.x]) {
			state->tableOfTime[currentVertex.y + 1][currentVertex.x] = newTime;
			struct Point vertexToBeChecked = { currentVertex.x, currentVertex.y + 1 };
			uncheckedVertices->push(vertexToBeChecked, state);
		}
	}
}

void rightCondition(State* state, Queue* uncheckedVertices, struct Point currentVertex) {
	if (currentVertex.x != state->width - 1 && state->tableOfHeightValues[currentVertex.y][currentVertex.x] >=
		state->tableOfHeightValues[currentVertex.y][currentVertex.x + 1]) {
		int newTime = state->tableOfTime[currentVertex.y][currentVertex.x] + EXTRAMINUTE;
		if (state->tableOfTime[currentVertex.y][currentVertex.x + 1] > newTime &&
			newTime < state->tableOfTime[state->endingPoint.y][state->endingPoint.x]) {
			state->tableOfTime[currentVertex.y][currentVertex.x + 1] = newTime;
			struct Point vertexToBeChecked = { currentVertex.x + 1, currentVertex.y };
			uncheckedVertices->push(vertexToBeChecked, state);
		}
	}
	else if (currentVertex.x != state->width - 1) {
		int heightDifference = state->tableOfHeightValues[currentVertex.y][currentVertex.x + 1] -
			state->tableOfHeightValues[currentVertex.y][currentVertex.x];
		int newTime = state->tableOfTime[currentVertex.y][currentVertex.x] + heightDifference + EXTRAMINUTE;
		if (state->tableOfTime[currentVertex.y][currentVertex.x + 1] > newTime &&
			newTime < state->tableOfTime[state->endingPoint.y][state->endingPoint.x]) {
			state->tableOfTime[currentVertex.y][currentVertex.x + 1] = newTime;
			struct Point vertexToBeChecked = { currentVertex.x + 1, currentVertex.y };
			uncheckedVertices->push(vertexToBeChecked, state);
		}
	}
}

void leftCondition(State* state, Queue* uncheckedVertices, struct Point currentVertex) {
	if (currentVertex.x != 0 && state->tableOfHeightValues[currentVertex.y][currentVertex.x] >=
		state->tableOfHeightValues[currentVertex.y][currentVertex.x - 1]) {
		int newTime = state->tableOfTime[currentVertex.y][currentVertex.x] + EXTRAMINUTE;
		if (state->tableOfTime[currentVertex.y][currentVertex.x - 1] > newTime &&
			newTime < state->tableOfTime[state->endingPoint.y][state->endingPoint.x]) {
			state->tableOfTime[currentVertex.y][currentVertex.x - 1] = newTime;
			struct Point vertexToBeChecked = { currentVertex.x - 1, currentVertex.y };
			uncheckedVertices->push(vertexToBeChecked, state);
		}
	}
	else if (currentVertex.x != 0) {
		int heightDifference = state->tableOfHeightValues[currentVertex.y][currentVertex.x - 1] -
			state->tableOfHeightValues[currentVertex.y][currentVertex.x];
		int newTime = state->tableOfTime[currentVertex.y][currentVertex.x] + heightDifference + EXTRAMINUTE;
		if (state->tableOfTime[currentVertex.y][currentVertex.x - 1] > newTime &&
			newTime < state->tableOfTime[state->endingPoint.y][state->endingPoint.x]) {
			state->tableOfTime[currentVertex.y][currentVertex.x - 1] = newTime;
			struct Point vertexToBeChecked = { currentVertex.x - 1, currentVertex.y };
			uncheckedVertices->push(vertexToBeChecked, state);
		}
	}
}

void dijkstraAlgorithm(State* state) {
	state->tableOfTime[state->startingPoint.y][state->startingPoint.x] = 0;
	Queue* uncheckedVertices = new Queue();
	uncheckedVertices->push(state->startingPoint, state);
	while (!uncheckedVertices->isEmpty()) {
		struct Point currentVertex = uncheckedVertices->pop();
		upCondition(state, uncheckedVertices, currentVertex);
		downCondition(state, uncheckedVertices, currentVertex);
		rightCondition(state, uncheckedVertices, currentVertex);
		leftCondition(state, uncheckedVertices, currentVertex);
		/*for (int y = 0; y < state->height; y++) {
			for (int x = 0; x < state->width; x++) {
				cout << state->tableOfTime[y][x] << ' ';
			}
			cout << endl;
		}*/
	}
	delete uncheckedVertices;
	cout << state->tableOfTime[state->endingPoint.y][state->endingPoint.x];
}

void dijkstraAlgorithmWithLifts(State* state) {
	state->tableOfTime[state->startingPoint.y][state->startingPoint.x] = 0;
	Queue* uncheckedVertices = new Queue();
	uncheckedVertices->push(state->startingPoint, state);
	while (!uncheckedVertices->isEmpty()) {
		struct Point currentVertex = uncheckedVertices->pop();
		upCondition(state, uncheckedVertices, currentVertex);
		downCondition(state, uncheckedVertices, currentVertex);
		rightCondition(state, uncheckedVertices, currentVertex);
		leftCondition(state, uncheckedVertices, currentVertex);
		for (int i = 0; i < state->numberOfLifts; i++) {
			if (state->lifts[i].stPoint.x == currentVertex.x && state->lifts[i].stPoint.y == currentVertex.y) {
				int waitingTime = state->lifts[i].departure -
					(state->tableOfTime[currentVertex.y][currentVertex.x] % state->lifts[i].departure);
				if (waitingTime == state->lifts[i].departure) {
					waitingTime = 0;
				}
				struct Point arrival = state->lifts[i].endPoint;
				int newTime = state->tableOfTime[currentVertex.y][currentVertex.x] + waitingTime + state->lifts[i].duration;
				if (newTime < state->tableOfTime[arrival.y][arrival.x]
					&& newTime < state->tableOfTime[state->endingPoint.y][state->endingPoint.y]) {
					state->tableOfTime[arrival.y][arrival.x] = newTime;
					uncheckedVertices->push(arrival, state);
				}
			}
		}
		/*for (int y = 0; y < state->height; y++) {
			for (int x = 0; x < state->width; x++) {
				cout << state->tableOfTime[y][x] << ' ';
			}
			cout << endl;
		}*/
	}
	delete uncheckedVertices;
	cout << state->tableOfTime[state->endingPoint.y][state->endingPoint.x];
}

int main() {
	struct State state;
	cin >> state.width;
	cin >> state.height;
	cin >> state.startingPoint.x;
	cin >> state.startingPoint.y;
	cin >> state.endingPoint.x;
	cin >> state.endingPoint.y;
	cin >> state.numberOfLifts;
	if (state.numberOfLifts == 0) {
		state.tableOfHeightValues = (int**)malloc(state.height * sizeof(int*));
		state.tableOfTime = (int**)malloc(state.height * sizeof(int*));
		for (int i = 0; i < state.height; i++) {
			state.tableOfHeightValues[i] = (int*)malloc(state.width * sizeof(int));
			state.tableOfTime[i] = (int*)malloc(state.width * sizeof(int));
			for (int j = 0; j < state.width; j++) {
				cin >> state.tableOfHeightValues[i][j];
				state.tableOfTime[i][j] = INT_MAX;
			}
		}
		dijkstraAlgorithm(&state);
	}
	else {
		state.lifts = (Lift*)malloc(state.numberOfLifts * sizeof(Lift));
		for (int i = 0; i < state.numberOfLifts; i++) {
			cin >> state.lifts[i].stPoint.x;
			cin >> state.lifts[i].stPoint.y;
			cin >> state.lifts[i].endPoint.x;
			cin >> state.lifts[i].endPoint.y;
			cin >> state.lifts[i].duration;
			cin >> state.lifts[i].departure;
		}
		state.tableOfHeightValues = (int**)malloc(state.height * sizeof(int*));
		state.tableOfTime = (int**)malloc(state.height * sizeof(int*));
		for (int i = 0; i < state.height; i++) {
			state.tableOfHeightValues[i] = (int*)malloc(state.width * sizeof(int));
			state.tableOfTime[i] = (int*)malloc(state.width * sizeof(int));
			for (int j = 0; j < state.width; j++) {
				cin >> state.tableOfHeightValues[i][j];
				state.tableOfTime[i][j] = INT_MAX;
			}
		}
		dijkstraAlgorithmWithLifts(&state);
	}
	return 0;
}
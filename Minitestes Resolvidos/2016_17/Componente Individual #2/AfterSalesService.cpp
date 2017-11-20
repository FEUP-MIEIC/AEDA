/*
 * AfterSalesService.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include <algorithm>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {
}

vector<Article*> AfterSalesService::getPresentsTable() const {
	return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
	return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
	return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
	for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
		presents[i]->setPresentNumber(i+1);
		presents[i]->setArrivalNumber(++tableOrdinal);
		presentsTable.push_back(presents[i]);
	}
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {

	vector<Article*> clientPresents;

	for(size_t i = 0; i < presentsTable.size(); i++)
	{
		Article * a = presentsTable.at(i);

		if(a->getClient() == client)
		{
			clientPresents.push_back(a);
			presentsTable.erase(presentsTable.begin() + i);
			i--;
		}
	}

	return clientPresents;
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */
bool compArticles(const Article* a1, const Article* a2)
{
	if(!a1->getDeliverHome() && a2->getDeliverHome())
		return true;
	else if(a1->getDeliverHome() && !a2->getDeliverHome())
		return false;
	else if(!a1->getDeliverHome() && !a2->getDeliverHome())
		return a1->getPresentNumber() + 2 < a2->getPresentNumber();
	else
		return false;
}
void AfterSalesService::sortArticles() {
	sort(presentsTable.begin(), presentsTable.begin() + 10, compArticles);
}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */
void AfterSalesService::enqueueArticles() {

	while(toWrap.size() < toWrapQueueSize && !presentsTable.empty())
	{
		Article* a = presentsTable.front();
		presentsTable.erase(presentsTable.begin(), presentsTable.begin() +1 );
		toWrap.push(a);
	}

}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {

	if(toWrap.empty()) return NULL;

	Article* a = toWrap.front();
	toWrap.pop();

	if(a->getDeliverHome()){
		toDeliver.push(a);
		return NULL;
	}


	return a;

}


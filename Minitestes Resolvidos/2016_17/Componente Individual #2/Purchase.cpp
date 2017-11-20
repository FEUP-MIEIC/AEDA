/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article *art = new Article(client, barCode);
	art->setPresent(present);
	art->setDeliverHome(deliverHome);

	return art;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	// check bag size
	if(bags.back().size() >= BAG_SIZE) // if last bag is full
	{
		stack<Article *> newBag;
		newBag.push(article);
		bags.push_back(newBag);
	}
	else
	{
		// add article to last bag
		bags.back().push(article);
	}


}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {

	vector<Article*> presents;
	list<stack<Article*>>::iterator it;

	for(it = bags.begin(); it != bags.end(); it++) // for each bag
	{
		stack<Article *> not_present; // auxiliar stack to store articles that are not presents
		stack<Article *> &bag = *it;
		/*
		 * Remove all articles from the bag.
		 * If the article is a present, add it to the vector 'presents'.
		 * Otherwise, push it to the auxiliar stack, 'not_present'
		 */
		while(!bag.empty())
		{
			Article* article = bag.top();
			if(article->getPresent()) // if it is a present ...
				presents.push_back(article);
			else
				not_present.push(article);

			// remove the article from the bag
			bag.pop();
		}


		/*
		 * All articles on not_present stack must be pushed back to the bag
		 */
		while(!not_present.empty())
		{
			bag.push(not_present.top());
			not_present.pop();
		}

	}
	return presents;

}


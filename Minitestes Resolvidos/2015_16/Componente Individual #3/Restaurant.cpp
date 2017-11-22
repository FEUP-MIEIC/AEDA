/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"
#include <iostream>

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)) {
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {

	stack<Dish *> &dishes = getCleanDishStack(collection, type);

	for(size_t i = 0; i < n; i++)
		dishes.push(new Dish(collection, type));
}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d = dirty.front();

	// remove from dirty queue
	dirty.pop();

	// place the dish on washed dishes list
	drying.push_back(d);

	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {

	if(idx < tables.size())
	{
		vector<Dish*> dirtyDishes = tables.at(idx).clear();
		for(size_t i = 0; i < dirtyDishes.size(); i++)
			dirty.push(dirtyDishes.at(i));
	}

}

/**
 * Stores in the respective clean stack all drying dishes of a given collection and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {

	stack<Dish *> &clean = getCleanDishStack(collection, type);

	list<Dish *>::iterator it;
	for(it = drying.begin(); it != drying.end(); it++)
	{
		if((*it)->getCollection() == collection && (*it)->getType() == type)
		{
			clean.push(*it);
			it = drying.erase(it);
		}
	}

}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {

	// check if table exists
	if(idx >= tables.size())
		return;

	// Get the table
	Table &t = tables.at(idx);

	// Verify if it's empty
	if(!t.empty())
		throw TableNotReadyException();

	// Get plate dishes of 'collection'
	stack<Dish *>& dishes = getCleanDishStack(collection, Plate);

	// Check if there are enough dishes for the table
	if(dishes.size() < t.size())
		throw NotEnoughDishesException();

	// Removes the dishes from the stack and store them in a vector
	vector<Dish *> aux;
	for(size_t i = 0; i < t.size(); i++)
	{
		aux.push_back(dishes.top());
		dishes.pop();
	}

	// call the function that places the dishes on the table
	t.putOn(aux);

}

/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped;

	// Copy the list of drying dishes
	dry_grouped = drying;

	// Group (sort)
	dry_grouped.sort([] (Dish* d1, Dish* d2) -> bool {
		if(d1->getCollection() == d2->getCollection())
			return d1->getType() < d2->getType();
		else
			return d1->getCollection() < d2->getCollection();
	});

	// Clear the list of drying dishes
	drying.clear();

	// return
	return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {

	list<Dish *>::const_iterator it;
	int counter = 0;
	for(it = grouped_dishes.cbegin(); it != grouped_dishes.cend(); it++)
	{
		string collection = (*it)->getCollection();
		TypeOfDish type = (*it)->getType();

		stack<Dish *> &cleanDishes = getCleanDishStack(collection, type);

		counter++;

		// loop through the list while the dishes are of same collection and type
		while(it != grouped_dishes.cend() && (*it)->getCollection() == collection && (*it)->getType() == type)
		{
			cleanDishes.push(*it);
			it++;
		}

		it--;

	}

	return counter;
}


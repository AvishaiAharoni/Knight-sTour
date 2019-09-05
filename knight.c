#include <assert.h> /* assert */
#include <stddef.h> /* size_t */
#include <stdio.h>	/* printf */
#include "barr.h"
#include "knight.h"

/******************************************************************************/

typedef struct delta
 {
 	int x;
 	int y;
 } delta_t;
 
typedef struct place
 {
 	int x;
 	int y;
 } place_t;
  
typedef struct dm
 {
 	delta_t delta;
 	size_t num_possible_moves;
 	
 } delta_and_num_possible_moves_t;

const delta_t possible_moves[] = { 
		{ +2, -1 },
		{ +2, +1 },
		{ +1, -2 },
		{ +1, +2 },
		
		{ -1, -2 },
		{ -1, +2 },
		{ -2, -1 },
		{ -2, +1 } };

/******************************************************************************/

int IsValidPlace(const place_t place, size_t size)
{
	return ((0 <= place.x) && (size - 1 >= place.x) &&
			(0 <= place.y) && (size - 1 >= place.y));
}

/******************************************************************************/

size_t GetSquereFromPlace(const place_t *place, size_t size)
{
	return (place->x * size + place->y);
}

/******************************************************************************/

int WasBeenInPlace(unsigned long moves, const place_t new_place, size_t size)
{
	return (BArrGetIsBitOn(moves, GetSquereFromPlace(&new_place, size)));
}

/******************************************************************************/

int RecKnightsTourCalc(
	const size_t size, 
	const place_t place, 
	const unsigned long visited,
	size_t good_moves[], 
	const size_t move_idx)
{
	size_t i = 0;
	size_t squere = 0;
	place_t new_place = { 0 };
	int res = 0;
	
	assert(0 < size);
/*	assert((0 <= place->x) && (size - 1 >= place->x));*/
/*	assert((0 <= place->y) && (size - 1 >= place->y));*/
	assert(NULL != possible_moves);
	
	
	
	if (BArrLUTCountBitsOn(visited) == size * size)
	{
/*		printf("x is %d and y  is %d\n", place.x, place.y);*/
		
		return (SUCSSESS);
	}
	
	
	for (i = 0; i < MAX_SIZE; ++i)
	{
		new_place.x = place.x;
		new_place.y = place.y;
		
		new_place.x += possible_moves[i].x;	
		new_place.y += possible_moves[i].y;
		
		if (1 == IsValidPlace(new_place, size) &&
		   (0 == WasBeenInPlace(visited, new_place, size)))
		{
			squere = GetSquereFromPlace(&new_place, size);
			
			good_moves[move_idx] = squere;
			
			res = RecKnightsTourCalc(
				size, 
				new_place, 
				BArrSetOneBitOn(visited, squere), 
				good_moves,
				move_idx + 1);
			if (SUCSSESS == res)
			{
				printf("x is %d and y  is %d\n", new_place.x, new_place.y);
		
				return (SUCSSESS);
			}
		}	
	}
	
/*	--idx_in_arr;*/
	
	return (NOT_FOUND);
}

/******************************************************************************/
 
int KnightsTour(size_t size, int x, int y)
{
	int res = 0;
	place_t place = { 0 };
	size_t squere = 0;
	unsigned long moves = 0;
	size_t good_moves[MAX_SIZE * MAX_SIZE] = { 0 };
	
	
	assert(0 < size);
	assert((0 <= x) && (size - 1 >= x));
	assert((0 <= y) && (size - 1 >= y));
	
	place.x = x;
	place.y = y;
	squere = GetSquereFromPlace(&place, size);
	
	good_moves[0] = squere;
	moves = BArrSetOneBitOn(moves, squere);
	
	res = RecKnightsTourCalc(size, place, moves, good_moves, 1);
	
	return (res);
}


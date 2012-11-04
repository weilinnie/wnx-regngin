/*
 * nfa.h
 *
 *  Created on: 2012-10-30
 *      Author: winiex
 */

#ifndef NFA_H_
#define NFA_H_

#define NULL_CHAR -1

struct NFA_STATE;
struct NFA_TRANS;
struct NFA;

typedef struct NFA_STATE NFA_STATE_T;
typedef struct NFA_STATE* NFA_STATE_TP;

typedef struct NFA_TRANS NFA_TRANS_T;
typedef struct NFA_TRANS* NFA_TRANS_TP;

typedef struct NFA NFA_T;
typedef struct NFA* NFA_TP;

typedef enum {
	STATE_TYPE_START, STATE_TYPE_MATCH, STATE_TYPE_TRANS
} NFA_STATE_TYPE_T;

typedef enum {
	TRANS_TYPE_CHAR, TRANS_TYPE_NULL
} NFA_TRANS_TYPE_T;

typedef enum {
	NFA_TYPE_CHAR,
	NFA_TYPE_OR,
	NFA_TYPE_CAT,
	NFA_TYPE_ONE_OR_MORE,
	NFA_TYPE_ONE_OR_NONE,
	NFA_TYPE_CLOSURE,
	NFA_TYPE_WHETHER
} NFA_TYPE_T;

struct NFA_STATE {
	NFA_STATE_TYPE_T state_type;
	NFA_TRANS_TP trans_in_head;
	NFA_TRANS_TP trans_out_head;
	NFA_STATE_TP state_prior;
	NFA_STATE_TP state_next;
};

struct NFA_TRANS {
	char trans_char;
	NFA_STATE_TP state_from;
	NFA_STATE_TP state_to;
	NFA_TRANS_TP trans_prior;
	NFA_TRANS_TP trans_next;
};

struct NFA {
	int state_count;
	NFA_TP inner_nfas;
	NFA_TP nfa_prior;
	NFA_TP nfa_next;
	NFA_STATE_TP nfa_states_head;
	NFA_STATE_TP nfa_start;
	NFA_STATE_TP nfa_match;
	NFA_TYPE_T nfa_type;
};

void nfa_regex_to_nfa(char* regex, NFA_TP* nfa_p);

void nfa_regex_postfix_to_nfa(char* regex_post, NFA_TP* nfa_p);

void nfa_construct_char_nfa(char char_elem, NFA_TP* nfa_p);

void nfa_construct_metachar_nfa(char meta_char_elem, NFA_TP* meta_nfa,
		NFA_TP nfa1, NFA_TP nfa2);

static void nfa_reform_or(NFA_TP nfa_reform_result, NFA_TP nfa1, NFA_TP nfa2);

static void nfa_reform_closure(NFA_TP nfa_reform_result, NFA_TP nfa);

static void nfa_reform_one_or_none(NFA_TP nfa_reform_result, NFA_TP nfa);

static void nfa_reform_cat(NFA_TP nfa_reform_result, NFA_TP nfa1, NFA_TP nfa2);

static void nfa_reform_one_or_more(NFA_TP nfa_reform_result, NFA_TP nfa);

#endif /* NFA_H_ */

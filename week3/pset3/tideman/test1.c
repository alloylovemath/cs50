#include <cs50.h>
#include <stdio.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pairs[0].winner = 0;
    pairs[0].loser = 1;
    pairs[1].winner = 1;
    pairs[1].loser = 2;
    pairs[2].winner = 2;
    pairs[2].loser = 3;
    pairs[3].winner = 3;
    pairs[3].loser = 1;

    pair_count = 4;

    lock_pairs();

        for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j])
            {
                printf("%i %i\n", i, j);
            }
        }
    }

    //print_winner();
    return 0;
}

//length of a string
int len(string s)
{
    int i = 0;

    while (s[i] != '\0')
    {
        i++;
    }

    return i;
}

//match two string
bool match(string s_1, string s_2)
{
    if (len(s_1) != len(s_2))
    {
        return false;
    }

    for (int i = 0; i < len(s_1); i++)
    {
        if (s_1[i] != s_2[i])
        {
            return false;
        }
    }

    return true;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (match(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j <candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    //bubble sort
    for (int i = 1; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i; j++)
        if (preferences[pairs[j].winner][pairs[j].loser] <= preferences[pairs[j+1].winner][pairs[j+1].loser])
        {
            int swap_1_1 = pairs[j].winner;
            int swap_1_2 = pairs[j].loser;
            int swap_2_1 = pairs[j+1].winner;
            int swap_2_2 = pairs[j+1].loser;

            pairs[j].winner = swap_2_1;
            pairs[j].loser = swap_2_2;
            pairs[j+1].winner = swap_1_1;
            pairs[j+1].winner = swap_1_2;
        }
    }
    return;
}

//link
bool link(int i, int j)
{
    int flag = 0;
    for (int L = 0; L < candidate_count; L++)
    {
        if (locked[i][L] == true)
        {
            flag += 1;
        }
    }

    if (flag == 0)
    {
        return false;
    }

    if (locked[i][j])
    {
        return true;
    }

    for (int L = 0; L < candidate_count; L++)
    {
        if (locked[i][L])
        {
            return link(L, j);
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        bool a = !link(pairs[i].loser, pairs[i].winner);
        int b = 0;
        if (!link(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            b += 1;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        int flag = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                flag += 1;
            }
        }
        if (flag == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
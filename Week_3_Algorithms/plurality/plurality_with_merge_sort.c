#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void merge_sort(candidate array[], int start, int end);
void merge(candidate array[], int start, int mid, int end);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    merge_sort(candidates, 0, candidate_count - 1);
    for (int i = candidate_count - 1; i >= 0; i--)
    {
        if (candidates[i].votes < candidates[candidate_count - 1].votes)
        {
            break;
        }
        printf("%s\n", candidates[i].name);
    }
}

void merge_sort(candidate array[], int start, int end)
{
    // if only 1 element, return
    if (end <= start)
    {
        return;
    }

    int mid = (start + end) / 2;
    // sort left half
    merge_sort(array, start, mid);
    // sort right half
    merge_sort(array, mid + 1, end);
    // merge halves
    merge(array, start, mid, end);
}

void merge(candidate array[], int start, int mid, int end)
{
    // create temp arrays with each half
    int lshift = 0;
    int len1 = mid - start + 1;
    candidate temp1[len1];
    for (int i = 0; i < len1; i++)
    {
        temp1[i] = array[i];
    }

    int rshift = 0;
    int len2 = end - mid;
    candidate temp2[len2];
    for (int i = 0; i < len2; i++)
    {
        temp2[i] = array[mid + 1 + i];
    }

    // take the smallest among the leftmost elements of
    // each temp array and add it to the main array until
    // we get to the end of one of the temp arrays
    int arr_iterator = 0;
    while (lshift < len1 && rshift < len2)
    {
        if (temp1[lshift].votes < temp2[rshift].votes)
        {
            array[start + arr_iterator] = temp1[lshift];
            lshift++;
        }
        else
        {
            array[start + arr_iterator] = temp2[rshift];
            rshift++;
        }
        arr_iterator++;
    }

    // for each remaining element in any array, add them to the main one
    while (lshift < len1)
    {
        array[start + arr_iterator] = temp1[lshift];
        lshift++;
        arr_iterator++;
    }

    while (rshift < len2)
    {
        array[start + arr_iterator] = temp2[rshift];
        rshift++;
        arr_iterator++;
    }
}

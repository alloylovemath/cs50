import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Invalid command line argument!")
        sys.exit(1)

    # TODO: Read database file into a variable
    STR_r = open(sys.argv[1], 'r')
    STRs = STR_r.readline().rstrip().split(',')[1:]
    STR_r.close()
    with open(sys.argv[1], 'r') as database:
        reader = csv.DictReader(database)
        database_ls = []
        for row in reader:
            database_ls.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as dna_sequence:
        sequence = dna_sequence.read()

    # TODO: Find longest match of each STR in DNA sequence
    sequence_dict = {}
    for STR in STRs:
        sequence_dict[STR] = longest_match(sequence, STR)

    # TODO: Check database for matching profiles
    match = False

    for i in range(len(database_ls)):
        points = 0

        for STR in STRs:
            if sequence_dict[STR] == int(database_ls[i][STR]):
                points = points + 1
        if points == len(STRs):
            print(database_ls[i]['name'])
            match = True
            break

    if match == False:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()

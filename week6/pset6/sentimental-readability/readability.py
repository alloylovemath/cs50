import string


def count_letters(text):
    num_letters = 0
    for c in text:
        if c in string.ascii_letters:
            num_letters += 1
    return num_letters


def count_words(text):
    n_s = text.split()
    return len(n_s)


def count_sentences(text):
    num_sentences = 0
    ends = ['.', '!', '?']
    for c in text:
        if c in ends:
            num_sentences += 1
    return num_sentences


def CLi(text):
    """calculate Coleman-Liau index"""
    W = count_words(text)
    aL = count_letters(text)
    aS = count_sentences(text)
    L = (aL / W) * 100
    S = (aS / W) * 100
    return (0.0588 * L - 0.296 * S - 15.8)


text = input("Text: ")
Grade = CLi(text)


if Grade < 1:
    print("Before Grade 1")
elif Grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(Grade)}")
import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        self.positives = []
        self.negatives = []

        with open(positives, 'r') as pos_file:
            lines = pos_file.readlines()             
            for word in lines:                       # citamo fajl liniju po liniju
                if word[0] != ";" and len(word) > 1: # preskacemo sve komentare koji pocinju sa ';' i prazne redove
                    self.positives.append(word[:-1]) # dodajemo rec u listu bez poslednjeg karaktera '\n'
                 
        with open(negatives, 'r') as neg_file:
            lines = neg_file.readlines()
            for word in lines:
                if word[0] != ";" and len(word) > 1:
                    self.negatives.append(word[:-1])


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        score = 0
        for word in text.split(" "):             # delimo ulazni tekst na reci
            if word.lower() in self.positives:   # ako se rec teksta nalazi u recniku pozitivnih reci
                score += 1
            elif word.lower() in self.negatives: # ako se rec teksta nalazi u recniku negativnih reci
                score -= 1
        return score

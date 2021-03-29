import os
from node import Node

def _cut_prefix(prefix, word):
    """
    test if ``prefix`` is a prefix of ``word``. If so, return the trailing part
    of ``word``, or ``None`` if not.
    """
    if word.startswith(prefix):
        return word[len(prefix):]

class Trie:
    def __init__(self):
        self.root = Node()

    def searchWord(self, word):
        """
        Check if the trie contains a given word.
        """
        if word == '' and self.root.endofWord:
            return True

        for prefix, child in self.root.children.items():
            trailing = _cut_prefix(prefix, word)
            if trailing is not None and trailing in child:
                return True

        return False 

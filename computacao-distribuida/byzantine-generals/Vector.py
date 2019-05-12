class Vector:
    vector = {}

    def __init__(self, vector={}):
        for key, value in vector.items():
            vector[key] = value

    def __repr__(self):
        return vector

    def __str__(self):
        return str(vector)


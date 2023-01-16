#include <bits/stdc++.h>
using namespace std;

/*
General Idea: Apply the Longest Common Subsequence (lcs) to words, by dividing the sentence into words and placing
them into an vector

Time Complexity: O(m*n) m,n = length of the vectors
*/

void lcs(vector<string> X, vector<string> Y, int m, int n)
{
    int L[m + 1][n + 1];

    // Algorithm lcs
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
            {
                L[i][j] = L[i - 1][j - 1] + 1;
            }
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    // Store the number of words in the sequence
    int index = L[m][n];

    //  Vector to store the final word
    vector<string> lcs(index, "");
    // Start on the right bottom corner
    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        // If the words are equal, sent them to the vector
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }

    // Print final vector
    long unsigned int z = 0;
    for (z = 0; z < lcs.size() - 1; z++)
    {
        cout << lcs[z] << " ";
    }
    cout << lcs[z] << endl;
}

int main()
{
    string a, b, line, l;
    a = b = "";
    bool out = false;
    // Read until EOF
    while (getline(cin, line))
    {
        a = b = ""; // Initialize as empty
        out = false;
        // In case it doesnt read # sore line in a and add ' '
        if (line.at(0) != '#')
            a += line + ' ';
        while (getline(cin, line))
        {
            if (line.at(0) == '#') // Same logic as above
            {
                out = true; // Stop
                break;
            }
            a += line + ' ';
            if (out)
                break;
        }
        out = false;               // Restart out
        while (getline(cin, line)) // Same logic as above but to b
        {
            if (line.at(0) == '#')
            {
                out = true;
                break;
            }
            b += line + ' ';
            if (out)
                break;
        }

        vector<string> str1, str2; // Word Vector
        string token;
        istringstream my_stream(a); // Stream to tokenize the sentences

        size_t pos = -1;
        while (my_stream >> token) // While its different from ' ' store in token
        {
            while ((pos = token.rfind(' ')) != string::npos) // Remove Space
            {
                token.erase(pos, 1);
            }
            str1.push_back(token); // Store Token in vector
        }
        istringstream my_stream2(b);
        while (my_stream2 >> token) // Same logic as above
        {
            while ((pos = token.rfind(' ')) != string::npos)
            {
                token.erase(pos, 1);
            }

            str2.push_back(token);
        }
        lcs(str1, str2, str1.size(), str2.size()); // Execute lcs
    }
}
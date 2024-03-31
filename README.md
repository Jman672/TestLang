# TestLang

### Grammar:
$$
\begin{align}
[\text{return}] &\to \text{return } [\text{expr}];
\\
[\text{expr}] &\to 
\begin{cases}
    \text{int\_lit}
    \\
    \text{[variable]}
\end{cases}
\\
[\text{variable}] &\to \text{assign (var\_name) = int\_lit}
\\
\end{align}
$$

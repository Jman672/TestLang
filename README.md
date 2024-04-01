# TestLang

### Grammar:
$$
\begin{align}
[\text{program}] &\to [\text{statement}]^*\\

[\text{statement}] &\to \begin{cases}
    return \text{  [expr];}\\
    assign \text{  [variable] = [expr];}\\
\end{cases}\\

[\text{expr}] &\to \begin{cases}
    \text{int\_lit}\\
    \text{[variable]}
\end{cases}\\

[\text{variable}] &\to \begin{cases}
    \text{int\_lit}\\
\end{cases}

\end{align}\\
$$

$$
\begin{align}
    [\text{prog}] &\to [\text{stmt}]^* \\
    [\text{stmt}] &\to
    \begin{cases}
        exit([\text{expr}]); \\
        type\space\text{ident} = [\text{expr}];
    \end{cases} \\
    [\text{expr}] &\to
    \begin{cases}
        \text{int\_lit} \\
        \text{ident}
    \end{cases} \\
    [\text{type}] &\to
    \begin{cases}
        \text{bool} \\
        \text{char} \mid \text{str} \\
        \text{byte} \mid \text{short} \mid \text{int} \mid \text{long} \\
        \text{ubyte} \mid \text{ushort} \mid \text{uint} \mid \text{ulong} \\
        \text{float} \mid \text{double} \\
        [\text{pointer}]^{*} \mid [\text{reference}]^{\&} \\
        \text{global} \\
        \text{void}
    \end{cases}
\end{align}
$$

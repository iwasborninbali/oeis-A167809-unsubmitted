# Proof

Let n>=1. A basis is a sequence 1=b₁<...<bₙ of integers. It is admissible when every x from 1 through bₙ is a sum of one or two basis elements, repetition allowed.

First, if S consists of k distinct positive integers below x and x<=2k, then two members of S, possibly equal, sum to x. Otherwise partition {1,...,x-1} into complementary pairs {t,x-t}. S can contain at most one element from each pair, and cannot contain the midpoint when x is even, since repetition is allowed. Thus |S|<=floor((x-1)/2)<=k-1, a contradiction.

Every increasing sequence satisfying bᵢ<=2i-1 is admissible. For x<=bₙ choose the least j with x<=bⱼ. If x=bⱼ it is a basis element. Otherwise the j-1 preceding elements are distinct and below x, and x<=bⱼ-1<=2(j-1), so the preceding lemma supplies a two-element sum. The case j=1 has no x<b₁, because b₁=1.

Now take a Dyck word of n up-steps and n down-steps, with no prefix containing more down-steps than up-steps, and let bᵢ be the position of its i-th up-step. Before that step there are i-1 up-steps and bᵢ-i down-steps, so bᵢ<=2i-1. Its first step is up, so b₁=1; the positions are strictly increasing. The previous paragraph makes these positions an admissible basis. They determine the entire word, so this map is injective.

There are Cₙ=binomial(2n,n)/(n+1) Dyck words: among the binomial(2n,n) balanced words, reflection of the prefix through the first step below zero bijects the bad ones with words having n+1 down-steps and n-1 up-steps. Their number is binomial(2n,n-1); subtraction gives Cₙ. Hence a(n)>=Cₙ for every n>=1. The proof is human-checkable, not formally machine-checked.

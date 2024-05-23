$$

	\begin{align*}
		\text{Regex} 			&::= \text{StartOfStringAnchor? Expression} \\
		\text{Expression} 		&::= \text{Subexpression} ( "|" \text{ Expression)?} \\
		\text{Subexpression}	&::= \text{SubexpressionItem+} \\
		\text{SubexpressionItem} &::= \begin{cases}
											\text{Match} \\
											\text{Group} \\
											\text{Anchor} \\
											\text{Backreference}
									 \end{cases} \\
		\text{Group} 			&::= \text{"(" GroupNonCapturingModifier? Expression ")" Quantifier?} \\
		\text{GroupNonCapturingModifier} &::= \text{"?:"} \\
		\text{Match} 			&::= \text{MatchItem Quantifier?} \\
		\text{MatchItem} 		&::= \begin{cases}
										\text{MatchAnyCharacter} \\
										\text{MatchCharacterClass} \\
										\text{MatchCharacter}
									\end{cases} \\
		\text{MatchAnyCharacter} &::= \text{"."} \\
		\text{MatchCharacterClass} &::= \begin{cases}
											\text{CharacterGroup} \\
											\text{CharacterClass} \\
											\text{CharacterClassFromUnicodeCategory}
										\end{cases} \\
		\text{MatchCharacter} &::= \text{Char} \\
		\text{CharacterGroup} &::= \text{"[" CharacterGroupNegativeModifier? CharacterGroupItem+ "]"} \\
		\text{CharacterGroupNegativeModifier} &::= "\char`\^" \\
		\text{CharacterGroupItem} &::= \begin{cases}
											\text{CharacterClass} \\
											\text{CharacterClassFromUnicodeCategory} \\
											\text{CharacterRange} \\
											\text{Char} \text{ /* excluding "]" */}
										\end{cases} \\
		\text{CharacterClass} &::= \begin{cases}
										\text{CharacterClassAnyWord} \\
										\text{CharacterClassAnyWordInverted} \\
										\text{CharacterClassAnyDecimalDigit} \\
										\text{CharacterClassAnyDecimalDigitInverted}
									\end{cases} \\
		\text{CharacterClassAnyWord} 		 &::= \text{"\textbackslash w"} \\
		\text{CharacterClassAnyWordInverted} &::= \text{"\textbackslash W"} \\
		\text{CharacterClassAnyDecimalDigit} &::= \text{"\textbackslash d"} \\
		\text{CharacterClassAnyDecimalDigitInverted} &::= \text{"\textbackslash D"} \\
		\text{CharacterClassFromUnicodeCategory} 	 &::= \text{"\textbackslash p"\{ UnicodeCategoryName \}} \\
		\text{UnicodeCategoryName} 			&::= \text{Letters} \\
		\text{CharacterRange} 	&::= \text{Char ("-" Char)?} \\
		\text{Quantifier} 		&::= \text{QuantifierType LazyModifier?} \\
		\text{QuantifierType} 	&::= \begin{cases}
										\text{ZeroOrMoreQuantifier} \\
										\text{OneOrMoreQuantifier} \\
										\text{ZeroOrOneQuantifier} \\
										\text{RangeQuantifier}
									\end{cases} \\
		\text{LazyModifier} 		&::= \text{"?"} \\
		\text{ZeroOrMoreQuantifier} &::= \text{"*"} \\
		\text{OneOrMoreQuantifier}  &::= \text{"+"} \\
		\text{ZeroOrOneQuantifier}  &::= \text{"?"} \\
		\text{RangeQuantifier} 		&::= \text{"\{" RangeQuantifierLowerBound ( "," RangeQuantifierUpperBound? )? "\}"} \\
		\text{RangeQuantifierLowerBound} &::= \text{Integer} \\
		\text{RangeQuantifierUpperBound} &::= \text{Integer} \\
		\text{Backreference} 		&::= \text{\textbackslash Integer} \\
		\text{StartOfStringAnchor}  &::= "\char`\^" \\
		\text{Anchor} 				&::= \begin{cases}
											\text{AnchorWordBoundary} \\
											\text{AnchorNonWordBoundary} \\
											\text{AnchorStartOfStringOnly} \\
											\text{AnchorEndOfStringOnlyNotNewline} \\
											\text{AnchorEndOfStringOnly} \\
											\text{AnchorPreviousMatchEnd} \\
											\text{AnchorEndOfString}
										\end{cases} \\
		\text{AnchorWordBoundary} &::= \text{"\textbackslash b"} \\
		\text{AnchorNonWordBoundary} &::= \text{"\textbackslash B"} \\
		\text{AnchorStartOfStringOnly} &::= \text{"\textbackslash A"} \\
		\text{AnchorEndOfStringOnlyNotNewline} &::= \text{"\textbackslash z"} \\
		\text{AnchorEndOfStringOnly} &::= \text{"\textbackslash Z"} \\
		\text{AnchorPreviousMatchEnd} &::= \text{"\textbackslash G"} \\
		\text{AnchorEndOfString} &::= \text{"\$"} \\
		\text{Integer} &::= \text{[0-9]+} \\
		\text{Letters} &::= \text{[a-zA-Z]+} \\
		\text{Char} &::= \begin{cases}
							\text{\#x9} \\
							\text{\#xA} \\
							\text{\#xD} \\
							\text{[\#x20-\#xD7FF]} \\
							\text{[\#xE000-\#xFFFD]} \\
							\text{[\#x10000-\#x10FFFF]}
						\end{cases}
	\end{align*}
$$

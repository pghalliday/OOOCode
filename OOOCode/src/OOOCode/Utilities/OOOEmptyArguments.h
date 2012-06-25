#ifndef OOOEmptyArguments_H
#define OOOEmptyArguments_H

/*
 * This stuff is derived directly from the following article by Jens Gustedt (June 8, 2010)
 *
 * http://gustedt.wordpress.com/2010/06/08/detect-empty-macro-arguments/
 */

/*
 * The following construct exposes the macro ISEMPTY that can be used to test
 * if a variadic argument list is empty or not. If the list is empty then it
 * expands to 1, if it is not then it will expand to 0
 *
 * This macro is limited to checking up to 15 arguments - if used to check an
 * argument list longer than this it will expand to something sort of undefined
 * (actually the 16th argument which in this context is undefined)
 *
 * The macro works by checking if the following construct expands to contain a comma...
 *
 *   _TRIGGER_PARENTHESIS_ ARGS ()
 *
 * using the property that a function macro only expands if it is followed by
 * parentheses otherwise it is not expanded at all.
 *
 * When expanded _TRIGGER_PARENTHESIS_() results in a comma. Thus if ARGS expands
 * to an empty argument list then this construct will expand to a comma.
 *
 * In order for the macro to work properly though it needs to discount a number
 * of false positive conditions.
 *
 * 1) We need to check that ARGS does not already contain a comma
 *
 * 2) We need to check that _TRIGGER_PARENTHESIS_ ARGS does not expand to anything
 * containing a comma
 *
 * 3) We need to check that ARGS() does not expand to anything containing a comma
 */

/*
 * This check for a comma works by expanding to 1 for argument lists of between 2 and 120 arguments
 * but 0 for argument lists of 1 argument (note that to the preprocessor an empty argument list
 * actually contains 1 argument which is the empty token)
 */
#define OOOArg121(                                             \
 _1, _2, _3, _4, _5, _6, _7, _8,                               \
 _9, _10, _11, _12, _13, _14, _15, _16,                        \
 _17, _18, _19, _20, _21, _22, _23, _24,                       \
 _25, _26, _27, _28, _29, _30, _31, _32,                       \
 _33, _34, _35, _36, _37, _38, _39, _40,                       \
 _41, _42, _43, _44, _45, _46, _47, _48,                       \
 _49, _50, _51, _52, _53, _54, _55, _56,                       \
 _57, _58, _59, _60, _61, _62, _63, _64,                       \
 _65, _66, _67, _68, _69, _70, _71, _72,                       \
 _73, _74, _75, _76, _77, _78, _79, _80,                       \
 _81, _82, _83, _84, _85, _86, _87, _88,                       \
 _89, _90, _91, _92, _93, _94, _95, _96,                       \
 _97, _98, _99, _100, _101, _102, _103, _104,                  \
 _105, _106, _107, _108, _109, _110, _111, _112,               \
 _113, _114, _115, _116, _117, _118, _119, _120,               \
 _121,                                                         \
 ARGS...) _121
#define OOOHasComma(ARGS...) OOOArg121(ARGS,                   \
 1, 1, 1, 1, 1, 1, 1,                                          \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1,                                       \
 1, 1, 1, 1, 1, 1, 1, 1, 0, 0)

/*
 * This stuff checks that the arguments passed to _OOOIsEmpty are (0, 0, 0, 1)
 */
#define OOOIsEmptyCase0001 ,
#define OOOPaste5(_0, _1, _2, _3, _4) _0 ## _1 ## _2 ## _3 ## _4
#define _OOOIsEmpty(_0, _1, _2, _3) OOOHasComma(OOOPaste5(OOOIsEmptyCase, _0, _1, _2, _3))

/*
 * This is the clever bit
 */
#define OOOTriggerParenthesis(ARGS...) ,
#define OOOIsEmpty(ARGS...)                                             \
_OOOIsEmpty(                                                            \
          OOOHasComma(ARGS),                                       		\
          OOOHasComma(OOOTriggerParenthesis ARGS),                 		\
          OOOHasComma(ARGS (/*empty*/)),                           		\
          OOOHasComma(OOOTriggerParenthesis ARGS (/*empty*/))      		\
          )

#endif

// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

/**
 ** \file /cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.hpp
 ** Define the blifparse::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_BLIFPARSE_CYGDRIVE_C_USERS_01100_DESKTOP_BACHELOR_ARBEIT_VPR_PROJECT_CMAKE_BUILD_DEBUG_LIBS_EXTERNAL_LIBBLIFPARSE_BLIF_PARSER_GEN_HPP_INCLUDED
# define YY_BLIFPARSE_CYGDRIVE_C_USERS_01100_DESKTOP_BACHELOR_ARBEIT_VPR_PROJECT_CMAKE_BUILD_DEBUG_LIBS_EXTERNAL_LIBBLIFPARSE_BLIF_PARSER_GEN_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 68 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:377

    #include <memory>
    #include "blifparse.hpp"
    #include "blif_lexer_fwd.hpp"

#line 50 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.hpp" // lalr1.cc:377

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"

#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef BLIFPARSE_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define BLIFPARSE_DEBUG 1
#  else
#   define BLIFPARSE_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define BLIFPARSE_DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined BLIFPARSE_DEBUG */

#line 34 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:377
namespace blifparse {
#line 135 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.hpp" // lalr1.cc:377



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class Parser
  {
  public:
#ifndef BLIFPARSE_STYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // attr
      char dummy1[sizeof(Attr)];

      // cname
      char dummy2[sizeof(Cname)];

      // conn
      char dummy3[sizeof(Conn)];

      // latch_type
      char dummy4[sizeof(LatchType)];

      // latch_init
      // logic_value
      char dummy5[sizeof(LogicValue)];

      // names
      char dummy6[sizeof(Names)];

      // param
      char dummy7[sizeof(Param)];

      // subckt
      char dummy8[sizeof(SubCkt)];

      // STRING
      // latch_control
      char dummy9[sizeof(std::string)];

      // so_cover_row
      char dummy10[sizeof(std::vector<LogicValue>)];

      // string_list
      char dummy11[sizeof(std::vector<std::string>)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef BLIFPARSE_STYPE semantic_type;
#endif

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m);
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOKEN_EOF = 0,
        TOKEN_DOT_NAMES = 258,
        TOKEN_DOT_LATCH = 259,
        TOKEN_DOT_MODEL = 260,
        TOKEN_DOT_SUBCKT = 261,
        TOKEN_DOT_INPUTS = 262,
        TOKEN_DOT_OUTPUTS = 263,
        TOKEN_DOT_CLOCK = 264,
        TOKEN_DOT_END = 265,
        TOKEN_DOT_BLACKBOX = 266,
        TOKEN_LATCH_FE = 267,
        TOKEN_LATCH_RE = 268,
        TOKEN_LATCH_AH = 269,
        TOKEN_LATCH_AL = 270,
        TOKEN_LATCH_AS = 271,
        TOKEN_NIL = 272,
        TOKEN_LATCH_INIT_2 = 273,
        TOKEN_LATCH_INIT_3 = 274,
        TOKEN_LOGIC_FALSE = 275,
        TOKEN_LOGIC_TRUE = 276,
        TOKEN_LOGIC_DONT_CARE = 277,
        TOKEN_EQ = 278,
        TOKEN_EOL = 279,
        TOKEN_DOT_CONN = 280,
        TOKEN_DOT_ATTR = 281,
        TOKEN_DOT_PARAM = 282,
        TOKEN_DOT_CNAME = 283,
        TOKEN_STRING = 284
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t);

  basic_symbol (typename Base::kind_type t, const Attr v);

  basic_symbol (typename Base::kind_type t, const Cname v);

  basic_symbol (typename Base::kind_type t, const Conn v);

  basic_symbol (typename Base::kind_type t, const LatchType v);

  basic_symbol (typename Base::kind_type t, const LogicValue v);

  basic_symbol (typename Base::kind_type t, const Names v);

  basic_symbol (typename Base::kind_type t, const Param v);

  basic_symbol (typename Base::kind_type t, const SubCkt v);

  basic_symbol (typename Base::kind_type t, const std::string v);

  basic_symbol (typename Base::kind_type t, const std::vector<LogicValue> v);

  basic_symbol (typename Base::kind_type t, const std::vector<std::string> v);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_EOF ();

    static inline
    symbol_type
    make_DOT_NAMES ();

    static inline
    symbol_type
    make_DOT_LATCH ();

    static inline
    symbol_type
    make_DOT_MODEL ();

    static inline
    symbol_type
    make_DOT_SUBCKT ();

    static inline
    symbol_type
    make_DOT_INPUTS ();

    static inline
    symbol_type
    make_DOT_OUTPUTS ();

    static inline
    symbol_type
    make_DOT_CLOCK ();

    static inline
    symbol_type
    make_DOT_END ();

    static inline
    symbol_type
    make_DOT_BLACKBOX ();

    static inline
    symbol_type
    make_LATCH_FE ();

    static inline
    symbol_type
    make_LATCH_RE ();

    static inline
    symbol_type
    make_LATCH_AH ();

    static inline
    symbol_type
    make_LATCH_AL ();

    static inline
    symbol_type
    make_LATCH_AS ();

    static inline
    symbol_type
    make_NIL ();

    static inline
    symbol_type
    make_LATCH_INIT_2 ();

    static inline
    symbol_type
    make_LATCH_INIT_3 ();

    static inline
    symbol_type
    make_LOGIC_FALSE ();

    static inline
    symbol_type
    make_LOGIC_TRUE ();

    static inline
    symbol_type
    make_LOGIC_DONT_CARE ();

    static inline
    symbol_type
    make_EQ ();

    static inline
    symbol_type
    make_EOL ();

    static inline
    symbol_type
    make_DOT_CONN ();

    static inline
    symbol_type
    make_DOT_ATTR ();

    static inline
    symbol_type
    make_DOT_PARAM ();

    static inline
    symbol_type
    make_DOT_CNAME ();

    static inline
    symbol_type
    make_STRING (const std::string& v);


    /// Build a parser object.
    Parser (Lexer& lexer_yyarg, Callback& callback_yyarg);
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if BLIFPARSE_DEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const signed char yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const signed char yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const signed char yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if BLIFPARSE_DEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned char yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 70,     ///< Last index in yytable_.
      yynnts_ = 15,  ///< Number of nonterminal symbols.
      yyfinal_ = 2, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 30  ///< Number of tokens.
    };


    // User arguments.
    Lexer& lexer;
    Callback& callback;
  };

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
    };
    const unsigned int user_token_number_max_ = 284;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
      switch (other.type_get ())
    {
      case 43: // attr
        value.copy< Attr > (other.value);
        break;

      case 42: // cname
        value.copy< Cname > (other.value);
        break;

      case 41: // conn
        value.copy< Conn > (other.value);
        break;

      case 37: // latch_type
        value.copy< LatchType > (other.value);
        break;

      case 35: // latch_init
      case 39: // logic_value
        value.copy< LogicValue > (other.value);
        break;

      case 32: // names
        value.copy< Names > (other.value);
        break;

      case 44: // param
        value.copy< Param > (other.value);
        break;

      case 33: // subckt
        value.copy< SubCkt > (other.value);
        break;

      case 29: // STRING
      case 36: // latch_control
        value.copy< std::string > (other.value);
        break;

      case 38: // so_cover_row
        value.copy< std::vector<LogicValue> > (other.value);
        break;

      case 40: // string_list
        value.copy< std::vector<std::string> > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value ()
  {
    (void) v;
      switch (this->type_get ())
    {
      case 43: // attr
        value.copy< Attr > (v);
        break;

      case 42: // cname
        value.copy< Cname > (v);
        break;

      case 41: // conn
        value.copy< Conn > (v);
        break;

      case 37: // latch_type
        value.copy< LatchType > (v);
        break;

      case 35: // latch_init
      case 39: // logic_value
        value.copy< LogicValue > (v);
        break;

      case 32: // names
        value.copy< Names > (v);
        break;

      case 44: // param
        value.copy< Param > (v);
        break;

      case 33: // subckt
        value.copy< SubCkt > (v);
        break;

      case 29: // STRING
      case 36: // latch_control
        value.copy< std::string > (v);
        break;

      case 38: // so_cover_row
        value.copy< std::vector<LogicValue> > (v);
        break;

      case 40: // string_list
        value.copy< std::vector<std::string> > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Attr v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Cname v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Conn v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const LatchType v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const LogicValue v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Names v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Param v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SubCkt v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<LogicValue> v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::string> v)
    : Base (t)
    , value (v)
  {}


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 43: // attr
        value.template destroy< Attr > ();
        break;

      case 42: // cname
        value.template destroy< Cname > ();
        break;

      case 41: // conn
        value.template destroy< Conn > ();
        break;

      case 37: // latch_type
        value.template destroy< LatchType > ();
        break;

      case 35: // latch_init
      case 39: // logic_value
        value.template destroy< LogicValue > ();
        break;

      case 32: // names
        value.template destroy< Names > ();
        break;

      case 44: // param
        value.template destroy< Param > ();
        break;

      case 33: // subckt
        value.template destroy< SubCkt > ();
        break;

      case 29: // STRING
      case 36: // latch_control
        value.template destroy< std::string > ();
        break;

      case 38: // so_cover_row
        value.template destroy< std::vector<LogicValue> > ();
        break;

      case 40: // string_list
        value.template destroy< std::vector<std::string> > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 43: // attr
        value.move< Attr > (s.value);
        break;

      case 42: // cname
        value.move< Cname > (s.value);
        break;

      case 41: // conn
        value.move< Conn > (s.value);
        break;

      case 37: // latch_type
        value.move< LatchType > (s.value);
        break;

      case 35: // latch_init
      case 39: // logic_value
        value.move< LogicValue > (s.value);
        break;

      case 32: // names
        value.move< Names > (s.value);
        break;

      case 44: // param
        value.move< Param > (s.value);
        break;

      case 33: // subckt
        value.move< SubCkt > (s.value);
        break;

      case 29: // STRING
      case 36: // latch_control
        value.move< std::string > (s.value);
        break;

      case 38: // so_cover_row
        value.move< std::vector<LogicValue> > (s.value);
        break;

      case 40: // string_list
        value.move< std::vector<std::string> > (s.value);
        break;

      default:
        break;
    }

  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Parser::token_type
  Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_EOF ()
  {
    return symbol_type (token::TOKEN_EOF);
  }

  Parser::symbol_type
  Parser::make_DOT_NAMES ()
  {
    return symbol_type (token::TOKEN_DOT_NAMES);
  }

  Parser::symbol_type
  Parser::make_DOT_LATCH ()
  {
    return symbol_type (token::TOKEN_DOT_LATCH);
  }

  Parser::symbol_type
  Parser::make_DOT_MODEL ()
  {
    return symbol_type (token::TOKEN_DOT_MODEL);
  }

  Parser::symbol_type
  Parser::make_DOT_SUBCKT ()
  {
    return symbol_type (token::TOKEN_DOT_SUBCKT);
  }

  Parser::symbol_type
  Parser::make_DOT_INPUTS ()
  {
    return symbol_type (token::TOKEN_DOT_INPUTS);
  }

  Parser::symbol_type
  Parser::make_DOT_OUTPUTS ()
  {
    return symbol_type (token::TOKEN_DOT_OUTPUTS);
  }

  Parser::symbol_type
  Parser::make_DOT_CLOCK ()
  {
    return symbol_type (token::TOKEN_DOT_CLOCK);
  }

  Parser::symbol_type
  Parser::make_DOT_END ()
  {
    return symbol_type (token::TOKEN_DOT_END);
  }

  Parser::symbol_type
  Parser::make_DOT_BLACKBOX ()
  {
    return symbol_type (token::TOKEN_DOT_BLACKBOX);
  }

  Parser::symbol_type
  Parser::make_LATCH_FE ()
  {
    return symbol_type (token::TOKEN_LATCH_FE);
  }

  Parser::symbol_type
  Parser::make_LATCH_RE ()
  {
    return symbol_type (token::TOKEN_LATCH_RE);
  }

  Parser::symbol_type
  Parser::make_LATCH_AH ()
  {
    return symbol_type (token::TOKEN_LATCH_AH);
  }

  Parser::symbol_type
  Parser::make_LATCH_AL ()
  {
    return symbol_type (token::TOKEN_LATCH_AL);
  }

  Parser::symbol_type
  Parser::make_LATCH_AS ()
  {
    return symbol_type (token::TOKEN_LATCH_AS);
  }

  Parser::symbol_type
  Parser::make_NIL ()
  {
    return symbol_type (token::TOKEN_NIL);
  }

  Parser::symbol_type
  Parser::make_LATCH_INIT_2 ()
  {
    return symbol_type (token::TOKEN_LATCH_INIT_2);
  }

  Parser::symbol_type
  Parser::make_LATCH_INIT_3 ()
  {
    return symbol_type (token::TOKEN_LATCH_INIT_3);
  }

  Parser::symbol_type
  Parser::make_LOGIC_FALSE ()
  {
    return symbol_type (token::TOKEN_LOGIC_FALSE);
  }

  Parser::symbol_type
  Parser::make_LOGIC_TRUE ()
  {
    return symbol_type (token::TOKEN_LOGIC_TRUE);
  }

  Parser::symbol_type
  Parser::make_LOGIC_DONT_CARE ()
  {
    return symbol_type (token::TOKEN_LOGIC_DONT_CARE);
  }

  Parser::symbol_type
  Parser::make_EQ ()
  {
    return symbol_type (token::TOKEN_EQ);
  }

  Parser::symbol_type
  Parser::make_EOL ()
  {
    return symbol_type (token::TOKEN_EOL);
  }

  Parser::symbol_type
  Parser::make_DOT_CONN ()
  {
    return symbol_type (token::TOKEN_DOT_CONN);
  }

  Parser::symbol_type
  Parser::make_DOT_ATTR ()
  {
    return symbol_type (token::TOKEN_DOT_ATTR);
  }

  Parser::symbol_type
  Parser::make_DOT_PARAM ()
  {
    return symbol_type (token::TOKEN_DOT_PARAM);
  }

  Parser::symbol_type
  Parser::make_DOT_CNAME ()
  {
    return symbol_type (token::TOKEN_DOT_CNAME);
  }

  Parser::symbol_type
  Parser::make_STRING (const std::string& v)
  {
    return symbol_type (token::TOKEN_STRING, v);
  }


#line 34 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:377
} // blifparse
#line 1466 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.hpp" // lalr1.cc:377




#endif // !YY_BLIFPARSE_CYGDRIVE_C_USERS_01100_DESKTOP_BACHELOR_ARBEIT_VPR_PROJECT_CMAKE_BUILD_DEBUG_LIBS_EXTERNAL_LIBBLIFPARSE_BLIF_PARSER_GEN_HPP_INCLUDED

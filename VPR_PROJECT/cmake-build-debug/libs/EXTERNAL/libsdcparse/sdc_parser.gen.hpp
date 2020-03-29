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
 ** \file /cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libsdcparse/sdc_parser.gen.hpp
 ** Define the sdcparse::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_SDCPARSE_CYGDRIVE_C_USERS_01100_DESKTOP_BACHELOR_ARBEIT_VPR_PROJECT_CMAKE_BUILD_DEBUG_LIBS_EXTERNAL_LIBSDCPARSE_SDC_PARSER_GEN_HPP_INCLUDED
# define YY_SDCPARSE_CYGDRIVE_C_USERS_01100_DESKTOP_BACHELOR_ARBEIT_VPR_PROJECT_CMAKE_BUILD_DEBUG_LIBS_EXTERNAL_LIBSDCPARSE_SDC_PARSER_GEN_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 68 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libsdcparse/src/sdc_parser.y" // lalr1.cc:377

    #include <memory>
    #include "sdcparse.hpp"
    #include "sdc_lexer_fwd.hpp"

#line 50 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libsdcparse/sdc_parser.gen.hpp" // lalr1.cc:377

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
#ifndef SDCPARSE_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define SDCPARSE_DEBUG 1
#  else
#   define SDCPARSE_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define SDCPARSE_DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined SDCPARSE_DEBUG */

#line 34 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libsdcparse/src/sdc_parser.y" // lalr1.cc:377
namespace sdcparse {
#line 135 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libsdcparse/sdc_parser.gen.hpp" // lalr1.cc:377



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
#ifndef SDCPARSE_STYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // cmd_create_clock
      char dummy1[sizeof(CreateClock)];

      // cmd_set_clock_groups
      char dummy2[sizeof(SetClockGroups)];

      // cmd_set_clock_latency
      char dummy3[sizeof(SetClockLatency)];

      // cmd_set_clock_uncertainty
      char dummy4[sizeof(SetClockUncertainty)];

      // cmd_set_disable_timing
      char dummy5[sizeof(SetDisableTiming)];

      // cmd_set_false_path
      char dummy6[sizeof(SetFalsePath)];

      // cmd_set_input_delay
      // cmd_set_output_delay
      char dummy7[sizeof(SetIoDelay)];

      // cmd_set_max_delay
      // cmd_set_min_delay
      char dummy8[sizeof(SetMinMaxDelay)];

      // cmd_set_multicycle_path
      char dummy9[sizeof(SetMulticyclePath)];

      // cmd_set_timing_derate
      char dummy10[sizeof(SetTimingDerate)];

      // cmd_get_ports
      // cmd_get_clocks
      // cmd_get_cells
      // cmd_get_pins
      // stringGroup
      char dummy11[sizeof(StringGroup)];

      // FLOAT_NUMBER
      // number
      // float_number
      char dummy12[sizeof(float)];

      // INT_NUMBER
      // int_number
      char dummy13[sizeof(int)];

      // STRING
      // ESCAPED_STRING
      // CHAR
      // string
      char dummy14[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef SDCPARSE_STYPE semantic_type;
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
        TOKEN_CMD_CREATE_CLOCK = 258,
        TOKEN_CMD_SET_CLOCK_GROUPS = 259,
        TOKEN_CMD_SET_FALSE_PATH = 260,
        TOKEN_CMD_SET_MAX_DELAY = 261,
        TOKEN_CMD_SET_MIN_DELAY = 262,
        TOKEN_CMD_SET_MULTICYCLE_PATH = 263,
        TOKEN_CMD_SET_INPUT_DELAY = 264,
        TOKEN_CMD_SET_OUTPUT_DELAY = 265,
        TOKEN_CMD_SET_CLOCK_UNCERTAINTY = 266,
        TOKEN_CMD_SET_CLOCK_LATENCY = 267,
        TOKEN_CMD_SET_DISABLE_TIMING = 268,
        TOKEN_CMD_SET_TIMING_DERATE = 269,
        TOKEN_CMD_GET_PORTS = 270,
        TOKEN_CMD_GET_CLOCKS = 271,
        TOKEN_CMD_GET_CELLS = 272,
        TOKEN_CMD_GET_PINS = 273,
        TOKEN_ARG_PERIOD = 274,
        TOKEN_ARG_WAVEFORM = 275,
        TOKEN_ARG_NAME = 276,
        TOKEN_ARG_EXCLUSIVE = 277,
        TOKEN_ARG_GROUP = 278,
        TOKEN_ARG_FROM = 279,
        TOKEN_ARG_TO = 280,
        TOKEN_ARG_SETUP = 281,
        TOKEN_ARG_HOLD = 282,
        TOKEN_ARG_CLOCK = 283,
        TOKEN_ARG_MAX = 284,
        TOKEN_ARG_MIN = 285,
        TOKEN_ARG_EARLY = 286,
        TOKEN_ARG_LATE = 287,
        TOKEN_ARG_CELL_DELAY = 288,
        TOKEN_ARG_NET_DELAY = 289,
        TOKEN_ARG_SOURCE = 290,
        TOKEN_LSPAR = 291,
        TOKEN_RSPAR = 292,
        TOKEN_LCPAR = 293,
        TOKEN_RCPAR = 294,
        TOKEN_EOL = 295,
        TOKEN_STRING = 296,
        TOKEN_ESCAPED_STRING = 297,
        TOKEN_CHAR = 298,
        TOKEN_FLOAT_NUMBER = 299,
        TOKEN_INT_NUMBER = 300
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

  basic_symbol (typename Base::kind_type t, const CreateClock v);

  basic_symbol (typename Base::kind_type t, const SetClockGroups v);

  basic_symbol (typename Base::kind_type t, const SetClockLatency v);

  basic_symbol (typename Base::kind_type t, const SetClockUncertainty v);

  basic_symbol (typename Base::kind_type t, const SetDisableTiming v);

  basic_symbol (typename Base::kind_type t, const SetFalsePath v);

  basic_symbol (typename Base::kind_type t, const SetIoDelay v);

  basic_symbol (typename Base::kind_type t, const SetMinMaxDelay v);

  basic_symbol (typename Base::kind_type t, const SetMulticyclePath v);

  basic_symbol (typename Base::kind_type t, const SetTimingDerate v);

  basic_symbol (typename Base::kind_type t, const StringGroup v);

  basic_symbol (typename Base::kind_type t, const float v);

  basic_symbol (typename Base::kind_type t, const int v);

  basic_symbol (typename Base::kind_type t, const std::string v);


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
    make_CMD_CREATE_CLOCK ();

    static inline
    symbol_type
    make_CMD_SET_CLOCK_GROUPS ();

    static inline
    symbol_type
    make_CMD_SET_FALSE_PATH ();

    static inline
    symbol_type
    make_CMD_SET_MAX_DELAY ();

    static inline
    symbol_type
    make_CMD_SET_MIN_DELAY ();

    static inline
    symbol_type
    make_CMD_SET_MULTICYCLE_PATH ();

    static inline
    symbol_type
    make_CMD_SET_INPUT_DELAY ();

    static inline
    symbol_type
    make_CMD_SET_OUTPUT_DELAY ();

    static inline
    symbol_type
    make_CMD_SET_CLOCK_UNCERTAINTY ();

    static inline
    symbol_type
    make_CMD_SET_CLOCK_LATENCY ();

    static inline
    symbol_type
    make_CMD_SET_DISABLE_TIMING ();

    static inline
    symbol_type
    make_CMD_SET_TIMING_DERATE ();

    static inline
    symbol_type
    make_CMD_GET_PORTS ();

    static inline
    symbol_type
    make_CMD_GET_CLOCKS ();

    static inline
    symbol_type
    make_CMD_GET_CELLS ();

    static inline
    symbol_type
    make_CMD_GET_PINS ();

    static inline
    symbol_type
    make_ARG_PERIOD ();

    static inline
    symbol_type
    make_ARG_WAVEFORM ();

    static inline
    symbol_type
    make_ARG_NAME ();

    static inline
    symbol_type
    make_ARG_EXCLUSIVE ();

    static inline
    symbol_type
    make_ARG_GROUP ();

    static inline
    symbol_type
    make_ARG_FROM ();

    static inline
    symbol_type
    make_ARG_TO ();

    static inline
    symbol_type
    make_ARG_SETUP ();

    static inline
    symbol_type
    make_ARG_HOLD ();

    static inline
    symbol_type
    make_ARG_CLOCK ();

    static inline
    symbol_type
    make_ARG_MAX ();

    static inline
    symbol_type
    make_ARG_MIN ();

    static inline
    symbol_type
    make_ARG_EARLY ();

    static inline
    symbol_type
    make_ARG_LATE ();

    static inline
    symbol_type
    make_ARG_CELL_DELAY ();

    static inline
    symbol_type
    make_ARG_NET_DELAY ();

    static inline
    symbol_type
    make_ARG_SOURCE ();

    static inline
    symbol_type
    make_LSPAR ();

    static inline
    symbol_type
    make_RSPAR ();

    static inline
    symbol_type
    make_LCPAR ();

    static inline
    symbol_type
    make_RCPAR ();

    static inline
    symbol_type
    make_EOL ();

    static inline
    symbol_type
    make_STRING (const std::string& v);

    static inline
    symbol_type
    make_ESCAPED_STRING (const std::string& v);

    static inline
    symbol_type
    make_CHAR (const std::string& v);

    static inline
    symbol_type
    make_FLOAT_NUMBER (const float& v);

    static inline
    symbol_type
    make_INT_NUMBER (const int& v);


    /// Build a parser object.
    Parser (Lexer& lexer_yyarg, Callback& callback_yyarg);
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if SDCPARSE_DEBUG
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
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const short int yycheck_[];

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
#if SDCPARSE_DEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
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
      yylast_ = 389,     ///< Last index in yytable_.
      yynnts_ = 23,  ///< Number of nonterminal symbols.
      yyfinal_ = 2, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 46  ///< Number of tokens.
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45
    };
    const unsigned int user_token_number_max_ = 300;
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
      case 48: // cmd_create_clock
        value.copy< CreateClock > (other.value);
        break;

      case 51: // cmd_set_clock_groups
        value.copy< SetClockGroups > (other.value);
        break;

      case 57: // cmd_set_clock_latency
        value.copy< SetClockLatency > (other.value);
        break;

      case 56: // cmd_set_clock_uncertainty
        value.copy< SetClockUncertainty > (other.value);
        break;

      case 58: // cmd_set_disable_timing
        value.copy< SetDisableTiming > (other.value);
        break;

      case 52: // cmd_set_false_path
        value.copy< SetFalsePath > (other.value);
        break;

      case 49: // cmd_set_input_delay
      case 50: // cmd_set_output_delay
        value.copy< SetIoDelay > (other.value);
        break;

      case 53: // cmd_set_max_delay
      case 54: // cmd_set_min_delay
        value.copy< SetMinMaxDelay > (other.value);
        break;

      case 55: // cmd_set_multicycle_path
        value.copy< SetMulticyclePath > (other.value);
        break;

      case 59: // cmd_set_timing_derate
        value.copy< SetTimingDerate > (other.value);
        break;

      case 60: // cmd_get_ports
      case 61: // cmd_get_clocks
      case 62: // cmd_get_cells
      case 63: // cmd_get_pins
      case 64: // stringGroup
        value.copy< StringGroup > (other.value);
        break;

      case 44: // FLOAT_NUMBER
      case 66: // number
      case 67: // float_number
        value.copy< float > (other.value);
        break;

      case 45: // INT_NUMBER
      case 68: // int_number
        value.copy< int > (other.value);
        break;

      case 41: // STRING
      case 42: // ESCAPED_STRING
      case 43: // CHAR
      case 65: // string
        value.copy< std::string > (other.value);
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
      case 48: // cmd_create_clock
        value.copy< CreateClock > (v);
        break;

      case 51: // cmd_set_clock_groups
        value.copy< SetClockGroups > (v);
        break;

      case 57: // cmd_set_clock_latency
        value.copy< SetClockLatency > (v);
        break;

      case 56: // cmd_set_clock_uncertainty
        value.copy< SetClockUncertainty > (v);
        break;

      case 58: // cmd_set_disable_timing
        value.copy< SetDisableTiming > (v);
        break;

      case 52: // cmd_set_false_path
        value.copy< SetFalsePath > (v);
        break;

      case 49: // cmd_set_input_delay
      case 50: // cmd_set_output_delay
        value.copy< SetIoDelay > (v);
        break;

      case 53: // cmd_set_max_delay
      case 54: // cmd_set_min_delay
        value.copy< SetMinMaxDelay > (v);
        break;

      case 55: // cmd_set_multicycle_path
        value.copy< SetMulticyclePath > (v);
        break;

      case 59: // cmd_set_timing_derate
        value.copy< SetTimingDerate > (v);
        break;

      case 60: // cmd_get_ports
      case 61: // cmd_get_clocks
      case 62: // cmd_get_cells
      case 63: // cmd_get_pins
      case 64: // stringGroup
        value.copy< StringGroup > (v);
        break;

      case 44: // FLOAT_NUMBER
      case 66: // number
      case 67: // float_number
        value.copy< float > (v);
        break;

      case 45: // INT_NUMBER
      case 68: // int_number
        value.copy< int > (v);
        break;

      case 41: // STRING
      case 42: // ESCAPED_STRING
      case 43: // CHAR
      case 65: // string
        value.copy< std::string > (v);
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
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const CreateClock v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SetClockGroups v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SetClockLatency v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SetClockUncertainty v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SetDisableTiming v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SetFalsePath v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SetIoDelay v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SetMinMaxDelay v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SetMulticyclePath v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SetTimingDerate v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const StringGroup v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const float v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v)
    : Base (t)
    , value (v)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v)
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
      case 48: // cmd_create_clock
        value.template destroy< CreateClock > ();
        break;

      case 51: // cmd_set_clock_groups
        value.template destroy< SetClockGroups > ();
        break;

      case 57: // cmd_set_clock_latency
        value.template destroy< SetClockLatency > ();
        break;

      case 56: // cmd_set_clock_uncertainty
        value.template destroy< SetClockUncertainty > ();
        break;

      case 58: // cmd_set_disable_timing
        value.template destroy< SetDisableTiming > ();
        break;

      case 52: // cmd_set_false_path
        value.template destroy< SetFalsePath > ();
        break;

      case 49: // cmd_set_input_delay
      case 50: // cmd_set_output_delay
        value.template destroy< SetIoDelay > ();
        break;

      case 53: // cmd_set_max_delay
      case 54: // cmd_set_min_delay
        value.template destroy< SetMinMaxDelay > ();
        break;

      case 55: // cmd_set_multicycle_path
        value.template destroy< SetMulticyclePath > ();
        break;

      case 59: // cmd_set_timing_derate
        value.template destroy< SetTimingDerate > ();
        break;

      case 60: // cmd_get_ports
      case 61: // cmd_get_clocks
      case 62: // cmd_get_cells
      case 63: // cmd_get_pins
      case 64: // stringGroup
        value.template destroy< StringGroup > ();
        break;

      case 44: // FLOAT_NUMBER
      case 66: // number
      case 67: // float_number
        value.template destroy< float > ();
        break;

      case 45: // INT_NUMBER
      case 68: // int_number
        value.template destroy< int > ();
        break;

      case 41: // STRING
      case 42: // ESCAPED_STRING
      case 43: // CHAR
      case 65: // string
        value.template destroy< std::string > ();
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
      case 48: // cmd_create_clock
        value.move< CreateClock > (s.value);
        break;

      case 51: // cmd_set_clock_groups
        value.move< SetClockGroups > (s.value);
        break;

      case 57: // cmd_set_clock_latency
        value.move< SetClockLatency > (s.value);
        break;

      case 56: // cmd_set_clock_uncertainty
        value.move< SetClockUncertainty > (s.value);
        break;

      case 58: // cmd_set_disable_timing
        value.move< SetDisableTiming > (s.value);
        break;

      case 52: // cmd_set_false_path
        value.move< SetFalsePath > (s.value);
        break;

      case 49: // cmd_set_input_delay
      case 50: // cmd_set_output_delay
        value.move< SetIoDelay > (s.value);
        break;

      case 53: // cmd_set_max_delay
      case 54: // cmd_set_min_delay
        value.move< SetMinMaxDelay > (s.value);
        break;

      case 55: // cmd_set_multicycle_path
        value.move< SetMulticyclePath > (s.value);
        break;

      case 59: // cmd_set_timing_derate
        value.move< SetTimingDerate > (s.value);
        break;

      case 60: // cmd_get_ports
      case 61: // cmd_get_clocks
      case 62: // cmd_get_cells
      case 63: // cmd_get_pins
      case 64: // stringGroup
        value.move< StringGroup > (s.value);
        break;

      case 44: // FLOAT_NUMBER
      case 66: // number
      case 67: // float_number
        value.move< float > (s.value);
        break;

      case 45: // INT_NUMBER
      case 68: // int_number
        value.move< int > (s.value);
        break;

      case 41: // STRING
      case 42: // ESCAPED_STRING
      case 43: // CHAR
      case 65: // string
        value.move< std::string > (s.value);
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
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
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
  Parser::make_CMD_CREATE_CLOCK ()
  {
    return symbol_type (token::TOKEN_CMD_CREATE_CLOCK);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_CLOCK_GROUPS ()
  {
    return symbol_type (token::TOKEN_CMD_SET_CLOCK_GROUPS);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_FALSE_PATH ()
  {
    return symbol_type (token::TOKEN_CMD_SET_FALSE_PATH);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_MAX_DELAY ()
  {
    return symbol_type (token::TOKEN_CMD_SET_MAX_DELAY);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_MIN_DELAY ()
  {
    return symbol_type (token::TOKEN_CMD_SET_MIN_DELAY);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_MULTICYCLE_PATH ()
  {
    return symbol_type (token::TOKEN_CMD_SET_MULTICYCLE_PATH);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_INPUT_DELAY ()
  {
    return symbol_type (token::TOKEN_CMD_SET_INPUT_DELAY);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_OUTPUT_DELAY ()
  {
    return symbol_type (token::TOKEN_CMD_SET_OUTPUT_DELAY);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_CLOCK_UNCERTAINTY ()
  {
    return symbol_type (token::TOKEN_CMD_SET_CLOCK_UNCERTAINTY);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_CLOCK_LATENCY ()
  {
    return symbol_type (token::TOKEN_CMD_SET_CLOCK_LATENCY);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_DISABLE_TIMING ()
  {
    return symbol_type (token::TOKEN_CMD_SET_DISABLE_TIMING);
  }

  Parser::symbol_type
  Parser::make_CMD_SET_TIMING_DERATE ()
  {
    return symbol_type (token::TOKEN_CMD_SET_TIMING_DERATE);
  }

  Parser::symbol_type
  Parser::make_CMD_GET_PORTS ()
  {
    return symbol_type (token::TOKEN_CMD_GET_PORTS);
  }

  Parser::symbol_type
  Parser::make_CMD_GET_CLOCKS ()
  {
    return symbol_type (token::TOKEN_CMD_GET_CLOCKS);
  }

  Parser::symbol_type
  Parser::make_CMD_GET_CELLS ()
  {
    return symbol_type (token::TOKEN_CMD_GET_CELLS);
  }

  Parser::symbol_type
  Parser::make_CMD_GET_PINS ()
  {
    return symbol_type (token::TOKEN_CMD_GET_PINS);
  }

  Parser::symbol_type
  Parser::make_ARG_PERIOD ()
  {
    return symbol_type (token::TOKEN_ARG_PERIOD);
  }

  Parser::symbol_type
  Parser::make_ARG_WAVEFORM ()
  {
    return symbol_type (token::TOKEN_ARG_WAVEFORM);
  }

  Parser::symbol_type
  Parser::make_ARG_NAME ()
  {
    return symbol_type (token::TOKEN_ARG_NAME);
  }

  Parser::symbol_type
  Parser::make_ARG_EXCLUSIVE ()
  {
    return symbol_type (token::TOKEN_ARG_EXCLUSIVE);
  }

  Parser::symbol_type
  Parser::make_ARG_GROUP ()
  {
    return symbol_type (token::TOKEN_ARG_GROUP);
  }

  Parser::symbol_type
  Parser::make_ARG_FROM ()
  {
    return symbol_type (token::TOKEN_ARG_FROM);
  }

  Parser::symbol_type
  Parser::make_ARG_TO ()
  {
    return symbol_type (token::TOKEN_ARG_TO);
  }

  Parser::symbol_type
  Parser::make_ARG_SETUP ()
  {
    return symbol_type (token::TOKEN_ARG_SETUP);
  }

  Parser::symbol_type
  Parser::make_ARG_HOLD ()
  {
    return symbol_type (token::TOKEN_ARG_HOLD);
  }

  Parser::symbol_type
  Parser::make_ARG_CLOCK ()
  {
    return symbol_type (token::TOKEN_ARG_CLOCK);
  }

  Parser::symbol_type
  Parser::make_ARG_MAX ()
  {
    return symbol_type (token::TOKEN_ARG_MAX);
  }

  Parser::symbol_type
  Parser::make_ARG_MIN ()
  {
    return symbol_type (token::TOKEN_ARG_MIN);
  }

  Parser::symbol_type
  Parser::make_ARG_EARLY ()
  {
    return symbol_type (token::TOKEN_ARG_EARLY);
  }

  Parser::symbol_type
  Parser::make_ARG_LATE ()
  {
    return symbol_type (token::TOKEN_ARG_LATE);
  }

  Parser::symbol_type
  Parser::make_ARG_CELL_DELAY ()
  {
    return symbol_type (token::TOKEN_ARG_CELL_DELAY);
  }

  Parser::symbol_type
  Parser::make_ARG_NET_DELAY ()
  {
    return symbol_type (token::TOKEN_ARG_NET_DELAY);
  }

  Parser::symbol_type
  Parser::make_ARG_SOURCE ()
  {
    return symbol_type (token::TOKEN_ARG_SOURCE);
  }

  Parser::symbol_type
  Parser::make_LSPAR ()
  {
    return symbol_type (token::TOKEN_LSPAR);
  }

  Parser::symbol_type
  Parser::make_RSPAR ()
  {
    return symbol_type (token::TOKEN_RSPAR);
  }

  Parser::symbol_type
  Parser::make_LCPAR ()
  {
    return symbol_type (token::TOKEN_LCPAR);
  }

  Parser::symbol_type
  Parser::make_RCPAR ()
  {
    return symbol_type (token::TOKEN_RCPAR);
  }

  Parser::symbol_type
  Parser::make_EOL ()
  {
    return symbol_type (token::TOKEN_EOL);
  }

  Parser::symbol_type
  Parser::make_STRING (const std::string& v)
  {
    return symbol_type (token::TOKEN_STRING, v);
  }

  Parser::symbol_type
  Parser::make_ESCAPED_STRING (const std::string& v)
  {
    return symbol_type (token::TOKEN_ESCAPED_STRING, v);
  }

  Parser::symbol_type
  Parser::make_CHAR (const std::string& v)
  {
    return symbol_type (token::TOKEN_CHAR, v);
  }

  Parser::symbol_type
  Parser::make_FLOAT_NUMBER (const float& v)
  {
    return symbol_type (token::TOKEN_FLOAT_NUMBER, v);
  }

  Parser::symbol_type
  Parser::make_INT_NUMBER (const int& v)
  {
    return symbol_type (token::TOKEN_INT_NUMBER, v);
  }


#line 34 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libsdcparse/src/sdc_parser.y" // lalr1.cc:377
} // sdcparse
#line 1777 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libsdcparse/sdc_parser.gen.hpp" // lalr1.cc:377




#endif // !YY_SDCPARSE_CYGDRIVE_C_USERS_01100_DESKTOP_BACHELOR_ARBEIT_VPR_PROJECT_CMAKE_BUILD_DEBUG_LIBS_EXTERNAL_LIBSDCPARSE_SDC_PARSER_GEN_HPP_INCLUDED

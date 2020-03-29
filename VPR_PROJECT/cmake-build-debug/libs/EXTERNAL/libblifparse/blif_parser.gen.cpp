// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

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
// //                    "%code top" blocks.
#line 74 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:397

    #include "blif_lexer.hpp"
    //Bison calls blifparse_lex() to get the next token.
    //We use the Lexer class as the interface to the lexer, so we
    //re-defined the function to tell Bison how to get the next token.
    static blifparse::Parser::symbol_type blifparse_lex(blifparse::Lexer& lexer) {
        return lexer.next_token();
    }

#line 44 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:397

// Take the name prefix into account.
#define yylex   blifparse_lex

// First part of user declarations.
#line 84 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:404


#include <stdio.h>
#include "assert.h"

#include "blifparse.hpp"
#include "blif_common.hpp"
#include "blif_error.hpp"

using namespace blifparse;


#line 63 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "blif_parser.gen.hpp"

// User implementation prologue.

#line 77 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if BLIFPARSE_DEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !BLIFPARSE_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !BLIFPARSE_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 34 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:479
namespace blifparse {
#line 144 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Lexer& lexer_yyarg, Callback& callback_yyarg)
    :
#if BLIFPARSE_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      callback (callback_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
      switch (that.type_get ())
    {
      case 43: // attr
        value.move< Attr > (that.value);
        break;

      case 42: // cname
        value.move< Cname > (that.value);
        break;

      case 41: // conn
        value.move< Conn > (that.value);
        break;

      case 37: // latch_type
        value.move< LatchType > (that.value);
        break;

      case 35: // latch_init
      case 39: // logic_value
        value.move< LogicValue > (that.value);
        break;

      case 32: // names
        value.move< Names > (that.value);
        break;

      case 44: // param
        value.move< Param > (that.value);
        break;

      case 33: // subckt
        value.move< SubCkt > (that.value);
        break;

      case 29: // STRING
      case 36: // latch_control
        value.move< std::string > (that.value);
        break;

      case 38: // so_cover_row
        value.move< std::vector<LogicValue> > (that.value);
        break;

      case 40: // string_list
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 43: // attr
        value.copy< Attr > (that.value);
        break;

      case 42: // cname
        value.copy< Cname > (that.value);
        break;

      case 41: // conn
        value.copy< Conn > (that.value);
        break;

      case 37: // latch_type
        value.copy< LatchType > (that.value);
        break;

      case 35: // latch_init
      case 39: // logic_value
        value.copy< LogicValue > (that.value);
        break;

      case 32: // names
        value.copy< Names > (that.value);
        break;

      case 44: // param
        value.copy< Param > (that.value);
        break;

      case 33: // subckt
        value.copy< SubCkt > (that.value);
        break;

      case 29: // STRING
      case 36: // latch_control
        value.copy< std::string > (that.value);
        break;

      case 38: // so_cover_row
        value.copy< std::vector<LogicValue> > (that.value);
        break;

      case 40: // string_list
        value.copy< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if BLIFPARSE_DEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if BLIFPARSE_DEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // BLIFPARSE_DEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (lexer));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 43: // attr
        yylhs.value.build< Attr > ();
        break;

      case 42: // cname
        yylhs.value.build< Cname > ();
        break;

      case 41: // conn
        yylhs.value.build< Conn > ();
        break;

      case 37: // latch_type
        yylhs.value.build< LatchType > ();
        break;

      case 35: // latch_init
      case 39: // logic_value
        yylhs.value.build< LogicValue > ();
        break;

      case 32: // names
        yylhs.value.build< Names > ();
        break;

      case 44: // param
        yylhs.value.build< Param > ();
        break;

      case 33: // subckt
        yylhs.value.build< SubCkt > ();
        break;

      case 29: // STRING
      case 36: // latch_control
        yylhs.value.build< std::string > ();
        break;

      case 38: // so_cover_row
        yylhs.value.build< std::vector<LogicValue> > ();
        break;

      case 40: // string_list
        yylhs.value.build< std::vector<std::string> > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 152 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { }
#line 648 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 3:
#line 153 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.begin_model(yystack_[1].value.as< std::string > ()); }
#line 654 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 4:
#line 154 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.inputs(yystack_[1].value.as< std::vector<std::string> > ()); }
#line 660 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 5:
#line 155 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.outputs(yystack_[1].value.as< std::vector<std::string> > ()); }
#line 666 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 6:
#line 156 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.names(yystack_[0].value.as< Names > ().nets, yystack_[0].value.as< Names > ().so_cover); }
#line 672 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 7:
#line 157 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { 
                                              if(yystack_[1].value.as< SubCkt > ().ports.size() != yystack_[1].value.as< SubCkt > ().nets.size()) {
                                                  blif_error_wrap(callback ,lexer.lineno()-1, lexer.text(), 
                                                    "Mismatched subckt port and net connection(s) size do not match"
                                                    " (%zu ports, %zu nets)", yystack_[1].value.as< SubCkt > ().ports.size(), yystack_[1].value.as< SubCkt > ().nets.size());
                                              }
                                              callback.lineno(lexer.lineno()-1); 
                                              callback.subckt(yystack_[1].value.as< SubCkt > ().model, yystack_[1].value.as< SubCkt > ().ports, yystack_[1].value.as< SubCkt > ().nets);
                                            }
#line 686 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 8:
#line 166 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { /*callback already called */ }
#line 692 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 9:
#line 167 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.blackbox(); }
#line 698 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 10:
#line 168 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.end_model(); }
#line 704 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 11:
#line 169 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.conn(yystack_[1].value.as< Conn > ().src, yystack_[1].value.as< Conn > ().dst); }
#line 710 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 12:
#line 170 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.cname(yystack_[1].value.as< Cname > ().name); }
#line 716 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 13:
#line 171 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.attr(yystack_[1].value.as< Attr > ().name, yystack_[1].value.as< Attr > ().value); }
#line 722 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 14:
#line 172 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { callback.lineno(lexer.lineno()-1); callback.param(yystack_[1].value.as< Param > ().name, yystack_[1].value.as< Param > ().value); }
#line 728 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 15:
#line 173 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { /* eat end-of-lines */}
#line 734 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 16:
#line 176 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< Names > () = Names(); yylhs.value.as< Names > ().nets = yystack_[1].value.as< std::vector<std::string> > (); }
#line 740 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 17:
#line 177 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { 
                                yylhs.value.as< Names > () = std::move(yystack_[2].value.as< Names > ()); 
                                if(yylhs.value.as< Names > ().nets.size() != yystack_[1].value.as< std::vector<LogicValue> > ().size()) {
                                    blif_error_wrap(callback, lexer.lineno()-1, lexer.text(),
                                        "Mismatched .names single-output cover row."
                                        " names connected to %zu net(s), but cover row has %zu element(s)",
                                        yylhs.value.as< Names > ().nets.size(), yystack_[1].value.as< std::vector<LogicValue> > ().size());
                                }
                                yylhs.value.as< Names > ().so_cover.push_back(yystack_[1].value.as< std::vector<LogicValue> > ()); 
                             }
#line 755 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 18:
#line 189 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< SubCkt > () = SubCkt(); yylhs.value.as< SubCkt > ().model = yystack_[0].value.as< std::string > (); }
#line 761 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 19:
#line 190 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< SubCkt > () = std::move(yystack_[3].value.as< SubCkt > ()); yylhs.value.as< SubCkt > ().ports.push_back(yystack_[2].value.as< std::string > ()); yylhs.value.as< SubCkt > ().nets.push_back(yystack_[0].value.as< std::string > ()); }
#line 767 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 20:
#line 193 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    {
                                    //Input and output only
                                    callback.lineno(lexer.lineno()); 
                                    callback.latch(yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::string > (), LatchType::UNSPECIFIED, "", LogicValue::UNKOWN);
                               }
#line 777 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 21:
#line 198 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    {
                                    //Input, output, type and control
                                    callback.lineno(lexer.lineno()); 
                                    callback.latch(yystack_[3].value.as< std::string > (), yystack_[2].value.as< std::string > (), yystack_[1].value.as< LatchType > (), yystack_[0].value.as< std::string > (), LogicValue::UNKOWN);
                               }
#line 787 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 22:
#line 203 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    {
                                    //Input, output, type, control and init-value
                                    callback.lineno(lexer.lineno()); 
                                    callback.latch(yystack_[4].value.as< std::string > (), yystack_[3].value.as< std::string > (), yystack_[2].value.as< LatchType > (), yystack_[1].value.as< std::string > (), yystack_[0].value.as< LogicValue > ());
                               }
#line 797 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 23:
#line 208 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    {
                                    //Input, output, and init-value
                                    callback.lineno(lexer.lineno());
                                    callback.latch(yystack_[2].value.as< std::string > (), yystack_[1].value.as< std::string > (), LatchType::UNSPECIFIED, "", yystack_[0].value.as< LogicValue > ());
                               }
#line 807 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 24:
#line 215 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LogicValue > () = LogicValue::TRUE; }
#line 813 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 25:
#line 216 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LogicValue > () = LogicValue::FALSE; }
#line 819 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 26:
#line 217 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LogicValue > () = LogicValue::DONT_CARE; }
#line 825 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 27:
#line 218 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LogicValue > () = LogicValue::UNKOWN; }
#line 831 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 28:
#line 221 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();}
#line 837 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 29:
#line 222 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = ""; }
#line 843 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 30:
#line 225 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LatchType > () = LatchType::FALLING_EDGE; }
#line 849 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 31:
#line 226 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LatchType > () = LatchType::RISING_EDGE; }
#line 855 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 32:
#line 227 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LatchType > () = LatchType::ACTIVE_HIGH; }
#line 861 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 33:
#line 228 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LatchType > () = LatchType::ACTIVE_LOW; }
#line 867 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 34:
#line 229 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LatchType > () = LatchType::ASYNCHRONOUS; }
#line 873 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 35:
#line 232 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<LogicValue> > () = std::vector<LogicValue>(); yylhs.value.as< std::vector<LogicValue> > ().push_back(yystack_[0].value.as< LogicValue > ()); }
#line 879 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 36:
#line 233 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<LogicValue> > () = std::move(yystack_[1].value.as< std::vector<LogicValue> > ()); yylhs.value.as< std::vector<LogicValue> > ().push_back(yystack_[0].value.as< LogicValue > ()); }
#line 885 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 37:
#line 236 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LogicValue > () = LogicValue::TRUE; }
#line 891 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 38:
#line 237 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LogicValue > () = LogicValue::FALSE; }
#line 897 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 39:
#line 238 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< LogicValue > () = LogicValue::DONT_CARE; }
#line 903 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 40:
#line 241 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>(); }
#line 909 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 41:
#line 242 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ()); yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ()); }
#line 915 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 42:
#line 248 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< Conn > () = Conn(); yylhs.value.as< Conn > ().src = yystack_[1].value.as< std::string > (); yylhs.value.as< Conn > ().dst = yystack_[0].value.as< std::string > (); }
#line 921 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 43:
#line 249 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< Cname > () = Cname(); yylhs.value.as< Cname > ().name = yystack_[0].value.as< std::string > (); }
#line 927 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 44:
#line 250 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< Attr > () = Attr(); yylhs.value.as< Attr > ().name = yystack_[1].value.as< std::string > (); yylhs.value.as< Attr > ().value = yystack_[0].value.as< std::string > (); }
#line 933 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 45:
#line 251 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< Attr > () = Attr(); yylhs.value.as< Attr > ().name = yystack_[0].value.as< std::string > (); yylhs.value.as< Attr > ().value = ""; }
#line 939 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 46:
#line 252 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< Param > () = Param(); yylhs.value.as< Param > ().name = yystack_[1].value.as< std::string > (); yylhs.value.as< Param > ().value = yystack_[0].value.as< std::string > (); }
#line 945 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;

  case 47:
#line 253 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:859
    { yylhs.value.as< Param > () = Param(); yylhs.value.as< Param > ().name = yystack_[0].value.as< std::string > (); yylhs.value.as< Param > ().value = ""; }
#line 951 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
    break;


#line 955 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -28;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
     -28,     0,   -28,   -28,   -27,   -20,   -17,   -28,   -28,    -5,
       9,   -28,    12,    23,    24,    26,    27,     5,    30,    32,
      33,    34,    35,     6,    31,    37,   -28,     7,     8,   -28,
     -28,    36,    38,    39,   -28,   -28,   -28,   -28,    18,   -28,
     -28,    40,   -28,   -28,   -28,   -28,   -28,   -28,   -28,     2,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,    41,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -16,
     -28,   -28,   -28,    25,   -28
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,     0,     1,    40,     0,     0,     0,    40,    40,     0,
       0,    15,     0,     0,     0,     0,     6,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,     0,    10,
       9,     0,    45,    47,    43,    38,    37,    39,     0,    35,
       7,     0,     8,    11,    12,    13,    14,    16,    41,    20,
       3,     4,     5,    42,    44,    46,    17,    36,     0,    30,
      31,    32,    33,    34,    26,    27,    25,    24,    23,     0,
      19,    29,    28,    21,    22
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -28,   -28,   -28,   -28,   -28,   -11,   -28,   -28,   -28,    28,
      43,   -28,   -28,   -28,   -28
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     1,    16,    17,    18,    68,    73,    69,    38,    39,
      23,    19,    20,    21,    22
  };

  const unsigned char
  Parser::yytable_[] =
  {
       2,    71,    24,     3,     4,     5,     6,     7,     8,    25,
       9,    10,    26,    72,    59,    60,    61,    62,    63,    29,
      64,    65,    66,    67,    11,    12,    13,    14,    15,    40,
      47,    51,    52,    30,    41,    48,    48,    48,    35,    36,
      37,    31,    56,    64,    65,    66,    67,    35,    36,    37,
      27,    28,    32,    33,    42,    34,    43,    44,    45,    46,
      49,    50,    74,    58,     0,    53,    57,    54,    55,     0,
      70
  };

  const signed char
  Parser::yycheck_[] =
  {
       0,    17,    29,     3,     4,     5,     6,     7,     8,    29,
      10,    11,    29,    29,    12,    13,    14,    15,    16,    24,
      18,    19,    20,    21,    24,    25,    26,    27,    28,    24,
      24,    24,    24,    24,    29,    29,    29,    29,    20,    21,
      22,    29,    24,    18,    19,    20,    21,    20,    21,    22,
       7,     8,    29,    29,    24,    29,    24,    24,    24,    24,
      29,    24,    73,    23,    -1,    29,    38,    29,    29,    -1,
      29
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    31,     0,     3,     4,     5,     6,     7,     8,    10,
      11,    24,    25,    26,    27,    28,    32,    33,    34,    41,
      42,    43,    44,    40,    29,    29,    29,    40,    40,    24,
      24,    29,    29,    29,    29,    20,    21,    22,    38,    39,
      24,    29,    24,    24,    24,    24,    24,    24,    29,    29,
      24,    24,    24,    29,    29,    29,    24,    39,    23,    12,
      13,    14,    15,    16,    18,    19,    20,    21,    35,    37,
      29,    17,    29,    36,    35
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    30,    31,    31,    31,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    32,    32,    33,    33,
      34,    34,    34,    34,    35,    35,    35,    35,    36,    36,
      37,    37,    37,    37,    37,    38,    38,    39,    39,    39,
      40,    40,    41,    42,    43,    43,    44,    44
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     4,     4,     4,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     2,     4,
       3,     5,     6,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     1,
       0,     2,     3,     2,     3,     2,     3,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end-of-file\"", "error", "$undefined", "\".names\"", "\".latch\"",
  "\".model\"", "\".subckt\"", "\".inputs\"", "\".outputs\"", "\".clock\"",
  "\".end\"", "\".blackbox\"", "\"fe\"", "\"re\"", "\"ah\"", "\"al\"",
  "\"as\"", "\"NIL\"", "\"2\"", "\"3\"", "\"0\"", "\"1\"", "\"-\"",
  "\"=\"", "\"end-of-line\"", "\".conn\"", "\".attr\"", "\".param\"",
  "\".cname\"", "STRING", "$accept", "blif_data", "names", "subckt",
  "latch", "latch_init", "latch_control", "latch_type", "so_cover_row",
  "logic_value", "string_list", "conn", "cname", "attr", "param", YY_NULLPTR
  };

#if BLIFPARSE_DEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,   152,   152,   153,   154,   155,   156,   157,   166,   167,
     168,   169,   170,   171,   172,   173,   176,   177,   189,   190,
     193,   198,   203,   208,   215,   216,   217,   218,   221,   222,
     225,   226,   227,   228,   229,   232,   233,   236,   237,   238,
     241,   242,   248,   249,   250,   251,   252,   253
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // BLIFPARSE_DEBUG


#line 34 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:1167
} // blifparse
#line 1368 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/cmake-build-debug/libs/EXTERNAL/libblifparse/blif_parser.gen.cpp" // lalr1.cc:1167
#line 255 "/cygdrive/c/Users/01100/Desktop/Bachelor_Arbeit/VPR_PROJECT/libs/EXTERNAL/libblifparse/src/blif_parser.y" // lalr1.cc:1168


void blifparse::Parser::error(const std::string& msg) {
    blif_error_wrap(callback, lexer.lineno(), lexer.text(), msg.c_str());
}

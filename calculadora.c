/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "calculadora.y" /* yacc.c:339  */

#include <iostream>
#include <fstream>
#include <math.h>
#include "tabla.c"
#include "string.h"
 

using namespace std;

bool real_final=false;
bool real=false;
bool error_mod=false;
bool error_log=false;
bool error_nodef = false;
bool error_bool_derecha = false;
bool cmp=false;
bool str = false;
bool error_str = false;
bool posVar = false;

int dimension_glob = 10;
int posEntrada_glob[2] = {0, 0};
int posSalida_glob[2] = {9, 9};
float pausa_glob = 0.5;

int posActual[2] = {0, 0};

Tabla* tabla;
tipo_datoTS* var;

//elementos externos al analizador sintácticos por haber sido declarados en el analizador léxico      			
extern int n_lineas;
extern int yylex();
extern FILE* yyin, yyout;


//definición de procedimientos auxiliares
void reset_flags(){
      real_final=false;
      real=false;
      error_mod=false;
      error_log=false;
      error_nodef = false;
      error_bool_derecha = false;
      cmp=false;
      str = false;
      error_str = false;
      posVar = false;
}

string check_tipo(){
      if(cmp) return "logico";
      else if(real_final) return "real";
      else return "entero";
}
int check_tipo_num(){
      if(str) return 3;
      else if(cmp) return 2;
      else if(real_final) return 1;
      else return 0;
}
void yyerror(const char* s){         /*    llamada por cada error sintactico de yacc */
	cout << "Error sintáctico en la línea \033[1;31m"<<n_lineas<<"\033[0m"<<endl;	
      reset_flags();
} 

bool insertar(tipo_datoTS *var, bool init, bool cte){
      if(init == true) var->init = true;
      else var->init = false;

      if(cte == true) var->cte = true;
      else var-> cte = false;

      return tabla->insertar(var);
}

void printTabla(ofstream &out){
      out << "*********************************" <<endl;
      out << "***NOMBRE      TIPO      VALOR***" <<endl;
      out << "*********************************" <<endl;

      nodo* n = tabla->getFirst();
      while(n!=NULL){
            out <<"**"<< n->dato.nombre<<"            ";
            if(n->dato.init == true){
                  switch (n->dato.tipo){
                        case 0: out << "Int          "<<n->dato.valor.valor_entero;break;
                        case 1: out << "Float        "<<n->dato.valor.valor_real;break;
                        case 2: out << "Bool         ";
                              if(n->dato.valor.valor_real)
                                    out<<"True";
                              else
                                    out<<"False";
                              break;
                        default: out << "undefined";break;
                        case 3: out << "String       "<<n->dato.valor.valor_cad;break;
                        case 4: out << "Position     <"<<n->dato.valor.valor_pos[0]<<","<<n->dato.valor.valor_pos[1]<<">";break;
                  }
            }
            else{
                 switch (n->dato.tipo){
                        case 0: out << "Int          NI";break;
                        case 1: out << "Float        NI";break;
                        case 2: out << "Bool         NI";break;
                        default: out << "undefined";break;
                        case 3: out << "String       NI";break;
                        case 4: out << "Position     NI";break;

                  } 
            }
            
            out <<endl;
            n=n->sig;
      }
      out << "*********************************" <<endl;
      out << "*******NI = No Inicializado******" <<endl;
      out << "*********************************" <<endl;

}

#line 188 "calculadora.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "calculadora.h".  */
#ifndef YY_YY_CALCULADORA_H_INCLUDED
# define YY_YY_CALCULADORA_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    ENTERO = 259,
    OBSTACULO = 260,
    VARIABLE = 261,
    ESCRIBIR = 262,
    CADENA = 263,
    DEFINICIONES = 264,
    CONFIGURACION = 265,
    OBSTACULOS = 266,
    EJEMPLOS = 267,
    DIMENSION = 268,
    ENTRADA = 269,
    SALIDA = 270,
    PAUSA = 271,
    NORTE = 272,
    SUR = 273,
    ESTE = 274,
    OESTE = 275,
    EJEMPLO = 276,
    FINEJEMPLO = 277,
    REPITE = 278,
    FINREPITE = 279,
    IF = 280,
    THEN = 281,
    ELSE = 282,
    ENDIF = 283,
    REAL = 284,
    INT = 285,
    FLOAT = 286,
    STRING = 287,
    POS = 288,
    OR = 289,
    AND = 290,
    NOT = 291,
    LE = 292,
    GE = 293,
    EQ = 294,
    NE = 295,
    menos = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 122 "calculadora.y" /* yacc.c:355  */

      //Tipo union por si en el futuro lo podemos usar
      typedef char tipo_cadena[50];
      typedef int tipo_pos[2];
      union tipo_valor{
            int valor_entero;//0
            float valor_real;//1
            bool valor_logico;//2
            tipo_cadena valor_cad;//3
            tipo_pos valor_pos;//4
      };

      int c_entero;
      float c_real;
      char c_cadena[20];
      bool c_bool;

#line 288 "calculadora.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CALCULADORA_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 305 "calculadora.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
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


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   564

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   296

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    47,     2,     2,
      49,    50,    45,    43,    54,    44,     2,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    53,    42,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    48,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   164,   164,   165,   166,   167,   168,   171,   218,   246,
     280,   314,   315,   322,   336,   340,   348,   355,   362,   369,
     377,   380,   381,   382,   396,   397,   398,   399,   400,   412,
     413,   423,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   447,   460,   603,   604,   605,   607,   608,   609,   610,
     611,   612,   613,   615,   616,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   628,   629,   631,   632,   633,   634,
     635,   636,   639
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "ENTERO", "OBSTACULO",
  "VARIABLE", "ESCRIBIR", "CADENA", "DEFINICIONES", "CONFIGURACION",
  "OBSTACULOS", "EJEMPLOS", "DIMENSION", "ENTRADA", "SALIDA", "PAUSA",
  "NORTE", "SUR", "ESTE", "OESTE", "EJEMPLO", "FINEJEMPLO", "REPITE",
  "FINREPITE", "IF", "THEN", "ELSE", "ENDIF", "REAL", "INT", "FLOAT",
  "STRING", "POS", "OR", "AND", "NOT", "LE", "GE", "EQ", "NE", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "'('", "')'", "menos",
  "'\\n'", "'='", "','", "$accept", "lista_instrucciones", "asignacion",
  "declaracion", "expr", "expr_logica", "bloque_definiciones",
  "bloque_configuracion", "bloque_obstaculos", "bloque_ejemplos",
  "bloque_ejemplos_anidado", "condicional", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,    60,    62,    43,    45,    42,    47,    37,    94,    40,
      41,   296,    10,    61,    44
};
# endif

#define YYPACT_NINF -131

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-131)))

#define YYTABLE_NINF -44

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     183,   -51,   -47,    82,   -25,   -18,    36,    50,    51,    60,
      73,   183,     7,    11,    68,  -131,  -131,  -131,    26,  -131,
     110,    31,   110,   296,   -26,   190,    69,  -131,  -131,  -131,
    -131,  -131,  -131,   183,    75,    35,    31,   312,   -20,  -131,
     164,  -131,    31,  -131,   328,   -22,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,  -131,   110,
     110,  -131,   190,    25,    79,    31,   133,  -131,  -131,  -131,
     191,  -131,  -131,   480,  -131,  -131,   516,   516,   516,   516,
     516,   516,   123,   123,    43,    43,    43,    43,    63,  -131,
    -131,   190,    54,   119,    56,   101,   131,    31,    31,  -131,
      69,     6,  -131,    31,   360,    31,   370,   380,   489,   298,
    -131,   271,   215,  -131,   336,  -131,  -131,    72,    77,    86,
      58,    88,    31,    31,    31,    31,    31,   110,  -131,  -131,
      31,    31,  -131,  -131,  -131,    89,    31,  -131,  -131,   390,
     400,   410,   420,   430,    49,   496,   503,   280,  -131,   348,
      94,  -131,  -131,  -131,  -131,  -131,    99,    91,   100,   103,
      31,    97,   301,   104,  -131,  -131,  -131,   510,   106,   109,
    -131,    94,   121,  -131,  -131,   248,  -131,   310,   122,    31,
      31,    31,    31,   129,  -131,  -131,   440,   450,   460,   470,
    -131,   223,  -131,  -131,  -131,  -131,   134,  -131
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,     0,    32,    22,    23,     0,    21,
       0,     0,     0,     0,     0,     0,    46,    15,    16,    17,
      18,     1,     5,     0,     0,     0,     0,     0,     0,    11,
       0,    42,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    12,     0,
       0,    13,     0,     0,     0,     0,     0,     6,    19,     8,
       0,     7,    10,     0,    24,    33,    36,    37,    38,    39,
      34,    35,    25,    26,    27,    28,    30,    29,    41,    40,
      45,     0,     0,    46,     0,     0,     0,     0,     0,    44,
      46,     0,    53,     0,     0,     0,     0,     0,     0,     0,
      47,     0,     0,    48,     0,    50,    52,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    63,    62,
       0,     0,     9,    53,    14,     0,     0,    60,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    55,     0,
       4,    59,    56,    57,    58,    53,     0,     0,     0,     0,
       0,     0,     0,     0,    49,    51,    64,     0,     0,     0,
      53,     3,     0,    66,    61,     0,    54,     0,     0,     0,
       0,     0,     0,     0,    71,    53,     0,     0,     0,     0,
      65,     0,    70,    67,    68,    69,     0,    72
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -131,    -9,     5,   -21,    -3,     9,   -55,   -83,  -130,   -32,
    -131,  -131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    10,   128,    12,    40,    24,    64,    66,   111,   150,
     177,   129
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    13,    32,   147,    63,    11,    14,    90,    59,    60,
     101,    37,    59,    60,    59,    60,    11,   109,    43,    44,
      95,    96,    97,    38,    67,   162,    61,    25,    75,    41,
      62,    45,    72,    70,    26,    16,    99,    17,    11,    73,
     175,    63,    27,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,   191,    28,    29,   110,    33,
      19,    34,    93,   -20,   135,   -20,    30,    62,    88,    89,
      63,    15,    16,    31,    17,    21,    35,    91,    39,    34,
      42,    68,    65,    59,    60,    15,    16,    69,    17,    92,
      18,    57,   104,   106,   107,   108,    62,    19,    60,   136,
     112,   156,   114,   168,    20,    16,   100,    17,   102,    36,
     137,    19,    21,    15,    16,   161,    17,    22,    20,   139,
     140,   141,   142,   143,   132,   163,    21,   145,   146,   133,
      19,    22,    65,   149,   171,    16,   144,    17,   134,    19,
     138,   148,   103,   164,    94,    21,    20,    95,    96,    97,
      42,     0,   165,     0,    21,   166,   170,   167,   173,    22,
      19,   174,    52,    53,    54,    55,    56,    57,    54,    55,
      56,    57,   105,   176,   185,    21,   186,   187,   188,   189,
      42,   190,   184,    -2,     1,     0,   197,     0,     0,     2,
       3,     1,     4,     5,     0,     0,     2,     3,     0,     0,
     -43,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,     6,     7,     8,     9,     0,     0,     0,
       6,     7,     8,     9,   119,     0,     0,     0,   120,     2,
       3,     0,     0,     0,    52,    53,    54,    55,    56,    57,
     122,   123,   124,   125,     0,    98,   126,     0,   127,   119,
       0,   196,     0,   120,     2,     3,     0,     0,    52,    53,
      54,    55,    56,    57,     0,   122,   123,   124,   125,   130,
       0,   126,   119,   127,     0,   178,   120,     2,     3,     0,
       0,   119,     0,   121,     0,   120,     2,     3,   122,   123,
     124,   125,   159,     0,   126,     0,   127,   122,   123,   124,
     125,     0,   119,   126,     0,   127,   120,     2,     3,   118,
       0,   119,    95,    96,    97,     0,     2,     3,   122,   123,
     124,   125,     0,     0,   126,   169,   127,   179,   180,   181,
     182,     0,   183,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,     0,     0,     0,    58,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,     0,     0,     0,    71,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,     0,    74,    52,
      53,    54,    55,    56,    57,     0,     0,     0,     0,     0,
     131,    52,    53,    54,    55,    56,    57,     0,     0,     0,
       0,     0,   160,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   113,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   115,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   116,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   151,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   152,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   153,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   154,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   155,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   192,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   193,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   194,    52,    53,    54,    55,    56,    57,     0,
       0,     0,   195,    52,    53,    54,    55,    56,    57,     0,
      74,   117,    52,    53,    54,    55,    56,    57,   157,    52,
      53,    54,    55,    56,    57,   158,    52,    53,    54,    55,
      56,    57,   172,    52,    53,    54,    55,    56,    57,    52,
      53,    54,    55,    56,    57
};

static const yytype_int16 yycheck[] =
{
       3,    52,    11,   133,    25,     0,    53,    62,    34,    35,
      93,    14,    34,    35,    34,    35,    11,   100,    21,    22,
      14,    15,    16,    14,    33,   155,    52,    52,    50,    20,
      25,    22,    52,    36,    52,     4,    91,     6,    33,    42,
     170,    62,     6,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,   185,     6,     6,    52,    52,
      29,    54,    65,    52,     6,    54,     6,    62,    59,    60,
      91,     3,     4,     0,     6,    44,     8,    52,    52,    54,
      49,     6,    13,    34,    35,     3,     4,    52,     6,    10,
       8,    48,    95,    96,    97,    98,    91,    29,    35,    41,
     103,    52,   105,     6,    36,     4,    52,     6,    52,    41,
      52,    29,    44,     3,     4,    21,     6,    49,    36,   122,
     123,   124,   125,   126,    52,    26,    44,   130,   131,    52,
      29,    49,    13,   136,   166,     4,   127,     6,    52,    29,
      52,    52,    41,    52,    11,    44,    36,    14,    15,    16,
      49,    -1,    52,    -1,    44,    52,    52,   160,    52,    49,
      29,    52,    43,    44,    45,    46,    47,    48,    45,    46,
      47,    48,    41,    52,    52,    44,   179,   180,   181,   182,
      49,    52,   177,     0,     1,    -1,    52,    -1,    -1,     6,
       7,     1,     9,    10,    -1,    -1,     6,     7,    -1,    -1,
      10,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    30,    31,    32,    33,    -1,    -1,    -1,
      30,    31,    32,    33,     1,    -1,    -1,    -1,     5,     6,
       7,    -1,    -1,    -1,    43,    44,    45,    46,    47,    48,
      17,    18,    19,    20,    -1,    54,    23,    -1,    25,     1,
      -1,    28,    -1,     5,     6,     7,    -1,    -1,    43,    44,
      45,    46,    47,    48,    -1,    17,    18,    19,    20,    54,
      -1,    23,     1,    25,    -1,    27,     5,     6,     7,    -1,
      -1,     1,    -1,    12,    -1,     5,     6,     7,    17,    18,
      19,    20,    12,    -1,    23,    -1,    25,    17,    18,    19,
      20,    -1,     1,    23,    -1,    25,     5,     6,     7,    11,
      -1,     1,    14,    15,    16,    -1,     6,     7,    17,    18,
      19,    20,    -1,    -1,    23,    24,    25,    17,    18,    19,
      20,    -1,    22,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    52,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    -1,    -1,    -1,    52,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    -1,    50,    43,
      44,    45,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
      54,    43,    44,    45,    46,    47,    48,    -1,    -1,    -1,
      -1,    -1,    54,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    52,    43,    44,    45,    46,    47,    48,    -1,
      50,    42,    43,    44,    45,    46,    47,    48,    42,    43,
      44,    45,    46,    47,    48,    42,    43,    44,    45,    46,
      47,    48,    42,    43,    44,    45,    46,    47,    48,    43,
      44,    45,    46,    47,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,     7,     9,    10,    30,    31,    32,    33,
      56,    57,    58,    52,    53,     3,     4,     6,     8,    29,
      36,    44,    49,    59,    60,    52,    52,     6,     6,     6,
       6,     0,    56,    52,    54,     8,    41,    59,    60,    52,
      59,    60,    49,    59,    59,    60,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    52,    34,
      35,    52,    57,    58,    61,    13,    62,    56,     6,    52,
      59,    52,    52,    59,    50,    50,    59,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    60,    60,
      61,    52,    10,    59,    11,    14,    15,    16,    54,    61,
      52,    62,    52,    41,    59,    41,    59,    59,    59,    62,
      52,    63,    59,    52,    59,    52,    52,    42,    11,     1,
       5,    12,    17,    18,    19,    20,    23,    25,    57,    66,
      54,    54,    52,    52,    52,     6,    41,    52,    52,    59,
      59,    59,    59,    59,    60,    59,    59,    63,    52,    59,
      64,    52,    52,    52,    52,    52,    52,    42,    42,    12,
      54,    21,    63,    26,    52,    52,    52,    59,     6,    24,
      52,    64,    42,    52,    52,    63,    52,    65,    27,    17,
      18,    19,    20,    22,    57,    52,    59,    59,    59,    59,
      52,    63,    52,    52,    52,    52,    28,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    56,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    58,
      58,    59,    59,    59,    59,    59,    59,    59,    59,    59,
      59,    59,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,    12,     9,     2,     3,     4,     4,     8,
       4,     3,     3,     3,     2,     2,     2,     2,     2,     3,
       2,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     0,     3,     2,     0,     4,     4,     8,
       4,     8,     4,     0,     8,     4,     4,     4,     4,     4,
       3,     7,     2,     2,     0,     7,     0,     4,     4,     4,
       4,     2,    11
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 164 "calculadora.y" /* yacc.c:1646  */
    {}
#line 1580 "calculadora.c" /* yacc.c:1646  */
    break;

  case 7:
#line 171 "calculadora.y" /* yacc.c:1646  */
    {if(!error_str&&!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                                
                                                if(tabla->buscar((yyvsp[-3].c_cadena), var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = (yyvsp[-1].c_real); break;
                                                                  case 1: var->valor.valor_real = (yyvsp[-1].c_real); break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-3].c_cadena)<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero";break;
                                                                  case 1: cout<<"real"  ;break;
                                                                  case 2: cout<<"logico";break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                            cout << " y no se le puede asignar tipo ";
                                                            switch (check_tipo_num()){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 0: var->valor.valor_entero = (yyvsp[-1].c_real); break;
                                                                  case 1: var->valor.valor_real = (yyvsp[-1].c_real); break;
                                                            }
                                                      if(!insertar(var,true, true))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      
                                                
                                          };
                                    
                                    reset_flags();
                                    }
#line 1632 "calculadora.c" /* yacc.c:1646  */
    break;

  case 8:
#line 218 "calculadora.y" /* yacc.c:1646  */
    {
                                                if(tabla->buscar((yyvsp[-3].c_cadena), var)!=0){
                                                      if(var->tipo == 3){
                                                            strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, (yyvsp[-1].c_cadena));
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-3].c_cadena)<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = 3;
                                                            strcpy(var->valor.valor_cad, (yyvsp[-1].c_cadena));
                                                      if(!insertar(var, true, true))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      reset_flags();
      }
#line 1665 "calculadora.c" /* yacc.c:1646  */
    break;

  case 9:
#line 246 "calculadora.y" /* yacc.c:1646  */
    {if(!real_final){
                                                      if(tabla->buscar((yyvsp[-7].c_cadena), var)!=0){
                                                            if(var->tipo == 4){
                                                                  strcpy(var->nombre, (yyvsp[-7].c_cadena));
                                                                  var->tipo = 4;
                                                                  var->valor.valor_pos[0] = (yyvsp[-4].c_real);
                                                                  var->valor.valor_pos[1] = (yyvsp[-2].c_real);
                                                                  if(!insertar(var, true, false))
                                                                        cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                            }
                                                            else{
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-7].c_cadena)<<" es de tipo ";
                                                                  switch (var->tipo){
                                                                        case 0: cout<<"entero"<<endl;break;
                                                                        case 1: cout<<"real"<<endl;break;
                                                                        case 2: cout<<"logico"<<endl;break;
                                                                        case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                        case 4: cout<<"posicion"<<endl;break;
                                                                  }
                                                            }
                                                      }
                                                      else{strcpy(var->nombre, (yyvsp[-7].c_cadena));
                                                                  strcpy(var->nombre, (yyvsp[-7].c_cadena));
                                                                  var->tipo = 4;
                                                                  var->valor.valor_pos[0] = (yyvsp[-4].c_real);
                                                                  var->valor.valor_pos[1] = (yyvsp[-2].c_real);
                                                            if(!insertar(var, true, true))
                                                                        cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                }
                                                else cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, las coordenadas de la posición deben ser valores enteros"<<endl;
                                                reset_flags();
                                          }
#line 1703 "calculadora.c" /* yacc.c:1646  */
    break;

  case 10:
#line 280 "calculadora.y" /* yacc.c:1646  */
    {if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha&&!error_str){
                                                
                                                if(tabla->buscar((yyvsp[-3].c_cadena), var) != 0){
                                                      if(var->tipo == check_tipo_num()){
                                                            strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = (yyvsp[-1].c_bool); break;
                                                            }
                                                            if(!insertar(var, true, false))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                                      else{
                                                            cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, la variable "<<(yyvsp[-3].c_cadena)<<" es de tipo ";
                                                            switch (var->tipo){
                                                                  case 0: cout<<"entero"<<endl;break;
                                                                  case 1: cout<<"real"<<endl;break;
                                                                  case 2: cout<<"logico"<<endl;break;
                                                                  case 3: cout<<"cadena de caracteres"<<endl;break;
                                                                  case 4: cout<<"posicion"<<endl;break;
                                                            }
                                                      }
                                                }
                                                else{strcpy(var->nombre, (yyvsp[-3].c_cadena));
                                                            var->tipo = check_tipo_num();
                                                            switch (var->tipo){
                                                                  case 2: var->valor.valor_logico = (yyvsp[-1].c_bool); break;
                                                            }
                                                      if(!insertar(var, true, true))
                                                                  cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                                      }
                                          };
                                    reset_flags();
                                    }
#line 1742 "calculadora.c" /* yacc.c:1646  */
    break;

  case 11:
#line 314 "calculadora.y" /* yacc.c:1646  */
    {cout << (yyvsp[-1].c_cadena) <<endl;reset_flags();}
#line 1748 "calculadora.c" /* yacc.c:1646  */
    break;

  case 12:
#line 315 "calculadora.y" /* yacc.c:1646  */
    {if(!error_str&&!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                    if(str){
                                          cout << var->valor.valor_cad <<endl;
                                    }
                                    else cout <<(yyvsp[-1].c_real)<<endl;
                              }
                              reset_flags();}
#line 1760 "calculadora.c" /* yacc.c:1646  */
    break;

  case 13:
#line 322 "calculadora.y" /* yacc.c:1646  */
    {
                                    if(!error_mod&&!error_log&&!error_nodef&&!error_bool_derecha){
                                                if(cmp){	
                                                      if((yyvsp[-1].c_bool))	
                                                            cout<<"true";	
                                                      else cout<<"false";	
                                                }	
                                                else	
                                                      cout<<(yyvsp[-1].c_bool);	
                                                cout<<endl;
                                    }
                                    reset_flags();
      }
#line 1778 "calculadora.c" /* yacc.c:1646  */
    break;

  case 14:
#line 336 "calculadora.y" /* yacc.c:1646  */
    {yyerrok;reset_flags();}
#line 1784 "calculadora.c" /* yacc.c:1646  */
    break;

  case 15:
#line 340 "calculadora.y" /* yacc.c:1646  */
    {
                              if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                    var->tipo=0;
                                    strcpy(var->nombre, (yyvsp[0].c_cadena));
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 1797 "calculadora.c" /* yacc.c:1646  */
    break;

  case 16:
#line 348 "calculadora.y" /* yacc.c:1646  */
    {if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                    var->tipo=1;
                                    strcpy(var->nombre, (yyvsp[0].c_cadena));
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 1809 "calculadora.c" /* yacc.c:1646  */
    break;

  case 17:
#line 355 "calculadora.y" /* yacc.c:1646  */
    {if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                    var->tipo=3;
                                    strcpy(var->nombre, (yyvsp[0].c_cadena));
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 1821 "calculadora.c" /* yacc.c:1646  */
    break;

  case 18:
#line 362 "calculadora.y" /* yacc.c:1646  */
    {if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                    var->tipo=4;
                                    strcpy(var->nombre, (yyvsp[0].c_cadena));
                                    if(!insertar(var, false, false))
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 1833 "calculadora.c" /* yacc.c:1646  */
    break;

  case 19:
#line 369 "calculadora.y" /* yacc.c:1646  */
    {int temp = var->tipo;
                                    if(tabla->buscar((yyvsp[0].c_cadena), var) == 0){
                                          strcpy(var->nombre, (yyvsp[0].c_cadena));
                                          var->tipo = temp;
                                          if(!insertar(var, false, false))
                                                cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m, intentando reasignar una constante"<<endl;
                                    }
                              }
#line 1846 "calculadora.c" /* yacc.c:1646  */
    break;

  case 20:
#line 377 "calculadora.y" /* yacc.c:1646  */
    {yyerrok;reset_flags();}
#line 1852 "calculadora.c" /* yacc.c:1646  */
    break;

  case 21:
#line 380 "calculadora.y" /* yacc.c:1646  */
    {real=true;real_final=true;(yyval.c_real)=(yyvsp[0].c_real);}
#line 1858 "calculadora.c" /* yacc.c:1646  */
    break;

  case 22:
#line 381 "calculadora.y" /* yacc.c:1646  */
    {(yyval.c_real)=(yyvsp[0].c_entero);}
#line 1864 "calculadora.c" /* yacc.c:1646  */
    break;

  case 23:
#line 382 "calculadora.y" /* yacc.c:1646  */
    {if(tabla->buscar((yyvsp[0].c_cadena), var) == 1){
                                    switch(var->tipo){
                                          case 0: (yyval.c_real)=var->valor.valor_entero;break;
                                          case 1: (yyval.c_real)=var->valor.valor_real;real=true;real_final=true;break;
                                          case 2: cout<<"Error semántico en la linea \033[1;31m"<<n_lineas+1<<"\033[0m, la variable "<<(yyvsp[0].c_cadena)<<" de tipo logico no puede estar en la parte derecha de la asignacion"<<endl;error_bool_derecha=true;break;
                                          case 3: str = true;break;
                                          case 4: posVar = true;break;
                                    }    
                              }
                              else{
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas+1<<"\033[0m, la variable "<<(yyvsp[0].c_cadena)<<" no ha sido definida previamente"<<endl;
                                    error_nodef = true;
                                    }
                              }
#line 1883 "calculadora.c" /* yacc.c:1646  */
    break;

  case 24:
#line 396 "calculadora.y" /* yacc.c:1646  */
    {(yyval.c_real)=(yyvsp[-1].c_real);}
#line 1889 "calculadora.c" /* yacc.c:1646  */
    break;

  case 25:
#line 397 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)=(yyvsp[-2].c_real)+(yyvsp[0].c_real);else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1895 "calculadora.c" /* yacc.c:1646  */
    break;

  case 26:
#line 398 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)=(yyvsp[-2].c_real)-(yyvsp[0].c_real);else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1901 "calculadora.c" /* yacc.c:1646  */
    break;

  case 27:
#line 399 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)=(yyvsp[-2].c_real)*(yyvsp[0].c_real);else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1907 "calculadora.c" /* yacc.c:1646  */
    break;

  case 28:
#line 400 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar){ 
                                    if(real){
                                          (yyval.c_real)=(float)((yyvsp[-2].c_real)/(yyvsp[0].c_real));
                                          real=false;
                                          }
                                    else{
                                          (yyval.c_real)=(int)((yyvsp[-2].c_real)/(yyvsp[0].c_real));
                                          };
                                    }
                              else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl; error_str = true;}
                              
                              }
#line 1924 "calculadora.c" /* yacc.c:1646  */
    break;

  case 29:
#line 412 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)=pow((yyvsp[-2].c_real),(yyvsp[0].c_real));else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1930 "calculadora.c" /* yacc.c:1646  */
    break;

  case 30:
#line 413 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) {if(!real){
                                          (yyval.c_real)=(int)(yyvsp[-2].c_real)%(int)(yyvsp[0].c_real);
                                          }
                                    else {
                                          error_mod=true;
                                          cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador % no se puede usar con datos de tipo real" <<endl;
                                          }
                                    }
                              else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}
                              }
#line 1945 "calculadora.c" /* yacc.c:1646  */
    break;

  case 31:
#line 423 "calculadora.y" /* yacc.c:1646  */
    {if(!str&&!posVar) (yyval.c_real)= -(yyvsp[0].c_real);else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1951 "calculadora.c" /* yacc.c:1646  */
    break;

  case 32:
#line 425 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;(yyval.c_bool)=(yyvsp[0].c_bool);}
#line 1957 "calculadora.c" /* yacc.c:1646  */
    break;

  case 33:
#line 426 "calculadora.y" /* yacc.c:1646  */
    {(yyval.c_bool)=(yyvsp[-1].c_bool);}
#line 1963 "calculadora.c" /* yacc.c:1646  */
    break;

  case 34:
#line 427 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) < (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1969 "calculadora.c" /* yacc.c:1646  */
    break;

  case 35:
#line 428 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) > (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1975 "calculadora.c" /* yacc.c:1646  */
    break;

  case 36:
#line 429 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) <= (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1981 "calculadora.c" /* yacc.c:1646  */
    break;

  case 37:
#line 430 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) >= (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1987 "calculadora.c" /* yacc.c:1646  */
    break;

  case 38:
#line 431 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) == (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1993 "calculadora.c" /* yacc.c:1646  */
    break;

  case 39:
#line 432 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;if(!str&&!posVar) {if((yyvsp[-2].c_real) != (yyvsp[0].c_real))(yyval.c_bool)=1;else (yyval.c_bool)=0;}else {cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m no se permiten operaciones con cadenas de caracteres o posiciones"<<endl;error_str = true;}}
#line 1999 "calculadora.c" /* yacc.c:1646  */
    break;

  case 40:
#line 433 "calculadora.y" /* yacc.c:1646  */
    {
                              cmp=true;
                              if(((yyvsp[-2].c_bool)==1||(yyvsp[-2].c_bool)==0)&&((yyvsp[0].c_bool)==1||(yyvsp[0].c_bool)==0))
                                    {if((yyvsp[-2].c_bool)==1 && (yyvsp[0].c_bool)==1)
                                          (yyval.c_bool)=1;
                                    else 
                                          (yyval.c_bool)=0;
                                    }
                              else{
                                    error_log=true;
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador AND sólo acepta expresiones tipo lógico" <<endl;
                                    }
                              }
#line 2017 "calculadora.c" /* yacc.c:1646  */
    break;

  case 41:
#line 447 "calculadora.y" /* yacc.c:1646  */
    {cmp=true;
                              if(((yyvsp[-2].c_bool)==1||(yyvsp[-2].c_bool)==0)&&((yyvsp[0].c_bool)==1||(yyvsp[0].c_bool)==0))
                              {     if((yyvsp[-2].c_bool)==1||(yyvsp[0].c_bool)==1)
                                          (yyval.c_bool)=1;
                                    else {
                                          (yyval.c_bool)=0;
                                          }
                                    }
                              else{
                                          error_log=true;
                                    cout<<"Error semántico en la linea \033[1;31m"<<n_lineas<<"\033[0m: el operador OR sólo acepta expresiones tipo lógico" <<endl;
                                    }    
                              }
#line 2035 "calculadora.c" /* yacc.c:1646  */
    break;

  case 42:
#line 460 "calculadora.y" /* yacc.c:1646  */
    {(yyval.c_bool)=!(yyvsp[0].c_bool);}
#line 2041 "calculadora.c" /* yacc.c:1646  */
    break;

  case 43:
#line 603 "calculadora.y" /* yacc.c:1646  */
    {}
#line 2047 "calculadora.c" /* yacc.c:1646  */
    break;

  case 46:
#line 607 "calculadora.y" /* yacc.c:1646  */
    {}
#line 2053 "calculadora.c" /* yacc.c:1646  */
    break;

  case 47:
#line 608 "calculadora.y" /* yacc.c:1646  */
    {reset_flags();}
#line 2059 "calculadora.c" /* yacc.c:1646  */
    break;

  case 48:
#line 609 "calculadora.y" /* yacc.c:1646  */
    {reset_flags();}
#line 2065 "calculadora.c" /* yacc.c:1646  */
    break;

  case 49:
#line 610 "calculadora.y" /* yacc.c:1646  */
    {reset_flags();}
#line 2071 "calculadora.c" /* yacc.c:1646  */
    break;

  case 50:
#line 611 "calculadora.y" /* yacc.c:1646  */
    {reset_flags();}
#line 2077 "calculadora.c" /* yacc.c:1646  */
    break;

  case 51:
#line 612 "calculadora.y" /* yacc.c:1646  */
    {reset_flags();}
#line 2083 "calculadora.c" /* yacc.c:1646  */
    break;

  case 52:
#line 613 "calculadora.y" /* yacc.c:1646  */
    {reset_flags();}
#line 2089 "calculadora.c" /* yacc.c:1646  */
    break;

  case 53:
#line 615 "calculadora.y" /* yacc.c:1646  */
    {}
#line 2095 "calculadora.c" /* yacc.c:1646  */
    break;

  case 55:
#line 617 "calculadora.y" /* yacc.c:1646  */
    {}
#line 2101 "calculadora.c" /* yacc.c:1646  */
    break;

  case 64:
#line 628 "calculadora.y" /* yacc.c:1646  */
    {}
#line 2107 "calculadora.c" /* yacc.c:1646  */
    break;

  case 65:
#line 629 "calculadora.y" /* yacc.c:1646  */
    {}
#line 2113 "calculadora.c" /* yacc.c:1646  */
    break;

  case 66:
#line 631 "calculadora.y" /* yacc.c:1646  */
    {}
#line 2119 "calculadora.c" /* yacc.c:1646  */
    break;


#line 2123 "calculadora.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 642 "calculadora.y" /* yacc.c:1906  */


int main(int argc, char *argv[]){
     tabla = (Tabla*)malloc(sizeof(Tabla));
     var = (tipo_datoTS*)malloc(sizeof(tipo_datoTS));
     n_lineas = 0;
     if (argc != 3) {
		cout <<"error en los argumentos"<<endl;
            cout <<endl<<"******************************************************"<<endl;
            cout <<"*      Calculadora de expresiones aritméticas        *"<<endl;
            cout <<"*                                                    *"<<endl;
            cout <<"*      1)con el prompt LISTO>                        *"<<endl;
            cout <<"*        teclea una expresión, por ej. 1+2<ENTER>    *"<<endl;
            cout <<"*        Este programa indicará                      *"<<endl;
            cout <<"*        si es gramaticalmente correcto              *"<<endl;
            cout <<"*      2)para terminar el programa                   *"<<endl;
            cout <<"*        teclear SALIR<ENTER>                        *"<<endl;
            cout <<"*      3)si se comete algun error en la expresión    *"<<endl;
            cout <<"*        se mostrará un mensaje y la ejecución       *"<<endl;
            cout <<"*        del programa finaliza                       *"<<endl;
            cout <<"******************************************************"<<endl<<endl<<endl;
            yyparse();
            cout <<"****************************************************"<<endl;
            cout <<"*                 ADIOS!!!!                        *"<<endl;
            cout <<"****************************************************"<<endl;
	}else {
     		yyin=fopen(argv[1],"rt");
     		n_lineas = 0;
       	yyparse();
            fclose(yyin);

            std::ofstream ofs (argv[2], std::ofstream::trunc);
            printTabla(ofs);
            ofs.close();

         	return 0;
	}
     return 0;
}

// THIS FILE WAS GENERATED VIA TRANSPILING. DO NOT MODIFY.
#pragma once

#include <gostd.hpp>

namespace gostd::unicode {

::gostd::Bool IsControl(::gostd::Rune r);

::gostd::Bool IsDigit(::gostd::Rune r);

::gostd::Bool IsGraphic(::gostd::Rune r);

::gostd::Bool IsLetter(::gostd::Rune r);

::gostd::Bool IsLower(::gostd::Rune r);

::gostd::Bool IsMark(::gostd::Rune r);

::gostd::Bool IsNumber(::gostd::Rune r);

::gostd::Bool IsPrint(::gostd::Rune r);

::gostd::Bool IsPunct(::gostd::Rune r);

::gostd::Bool IsSpace(::gostd::Rune r);

::gostd::Bool IsSymbol(::gostd::Rune r);

::gostd::Bool IsTitle(::gostd::Rune r);

::gostd::Bool IsUpper(::gostd::Rune r);

constexpr auto LowerCase = ::gostd::UntypedConstant(1);

constexpr auto MaxASCII = ::gostd::UntypedConstant(127);

constexpr auto MaxCase = ::gostd::UntypedConstant(3);

constexpr auto MaxLatin1 = ::gostd::UntypedConstant(255);

constexpr auto MaxRune = ::gostd::UntypedConstant(1114111);

struct Range16 {
    ::gostd::Uint16 Lo;
    ::gostd::Uint16 Hi;
    ::gostd::Uint16 Stride;
};

struct Range32 {
    ::gostd::Uint32 Lo;
    ::gostd::Uint32 Hi;
    ::gostd::Uint32 Stride;
};

struct RangeTable {
    ::gostd::Slice<Range16> R16;
    ::gostd::Slice<Range32> R32;
    ::gostd::Int LatinOffset;
};

extern ::gostd::Ptr<RangeTable> ASCII_Hex_Digit;

extern ::gostd::Ptr<RangeTable> Adlam;

extern ::gostd::Ptr<RangeTable> Ahom;

extern ::gostd::Ptr<RangeTable> Anatolian_Hieroglyphs;

extern ::gostd::Ptr<RangeTable> Arabic;

extern ::gostd::Ptr<RangeTable> Armenian;

extern ::gostd::Ptr<RangeTable> Avestan;

extern ::gostd::Ptr<RangeTable> Balinese;

extern ::gostd::Ptr<RangeTable> Bamum;

extern ::gostd::Ptr<RangeTable> Bassa_Vah;

extern ::gostd::Ptr<RangeTable> Batak;

extern ::gostd::Ptr<RangeTable> Bengali;

extern ::gostd::Ptr<RangeTable> Bhaiksuki;

extern ::gostd::Ptr<RangeTable> Bidi_Control;

extern ::gostd::Ptr<RangeTable> Bopomofo;

extern ::gostd::Ptr<RangeTable> Brahmi;

extern ::gostd::Ptr<RangeTable> Braille;

extern ::gostd::Ptr<RangeTable> Buginese;

extern ::gostd::Ptr<RangeTable> Buhid;

extern ::gostd::Ptr<RangeTable> C;

extern ::gostd::Ptr<RangeTable> Canadian_Aboriginal;

extern ::gostd::Ptr<RangeTable> Carian;

extern ::gostd::Map<::gostd::String, ::gostd::Ptr<RangeTable>> Categories;

extern ::gostd::Ptr<RangeTable> Caucasian_Albanian;

extern ::gostd::Ptr<RangeTable> Cc;

extern ::gostd::Ptr<RangeTable> Cf;

extern ::gostd::Ptr<RangeTable> Chakma;

extern ::gostd::Ptr<RangeTable> Cham;

extern ::gostd::Ptr<RangeTable> Cherokee;

extern ::gostd::Ptr<RangeTable> Co;

extern ::gostd::Ptr<RangeTable> Common;

extern ::gostd::Ptr<RangeTable> Coptic;

extern ::gostd::Ptr<RangeTable> Cs;

extern ::gostd::Ptr<RangeTable> Cuneiform;

extern ::gostd::Ptr<RangeTable> Cypriot;

extern ::gostd::Ptr<RangeTable> Cyrillic;

extern ::gostd::Ptr<RangeTable> Dash;

extern ::gostd::Ptr<RangeTable> Deprecated;

extern ::gostd::Ptr<RangeTable> Deseret;

extern ::gostd::Ptr<RangeTable> Devanagari;

extern ::gostd::Ptr<RangeTable> Diacritic;

extern ::gostd::Ptr<RangeTable> Digit;

extern ::gostd::Ptr<RangeTable> Duployan;

extern ::gostd::Ptr<RangeTable> Egyptian_Hieroglyphs;

extern ::gostd::Ptr<RangeTable> Elbasan;

extern ::gostd::Ptr<RangeTable> Ethiopic;

extern ::gostd::Ptr<RangeTable> Extender;

extern ::gostd::Map<::gostd::String, ::gostd::Ptr<RangeTable>> FoldCategory;

extern ::gostd::Map<::gostd::String, ::gostd::Ptr<RangeTable>> FoldScript;

extern ::gostd::Ptr<RangeTable> Georgian;

extern ::gostd::Ptr<RangeTable> Glagolitic;

extern ::gostd::Ptr<RangeTable> Gothic;

extern ::gostd::Ptr<RangeTable> Grantha;

extern ::gostd::Slice<::gostd::Ptr<RangeTable>> GraphicRanges;

extern ::gostd::Ptr<RangeTable> Greek;

extern ::gostd::Ptr<RangeTable> Gujarati;

extern ::gostd::Ptr<RangeTable> Gurmukhi;

extern ::gostd::Ptr<RangeTable> Han;

extern ::gostd::Ptr<RangeTable> Hangul;

extern ::gostd::Ptr<RangeTable> Hanunoo;

extern ::gostd::Ptr<RangeTable> Hatran;

extern ::gostd::Ptr<RangeTable> Hebrew;

extern ::gostd::Ptr<RangeTable> Hex_Digit;

extern ::gostd::Ptr<RangeTable> Hiragana;

extern ::gostd::Ptr<RangeTable> Hyphen;

extern ::gostd::Ptr<RangeTable> IDS_Binary_Operator;

extern ::gostd::Ptr<RangeTable> IDS_Trinary_Operator;

extern ::gostd::Ptr<RangeTable> Ideographic;

extern ::gostd::Ptr<RangeTable> Imperial_Aramaic;

::gostd::Bool In(::gostd::Rune r, ::gostd::Slice<::gostd::Ptr<RangeTable>> ranges);

extern ::gostd::Ptr<RangeTable> Inherited;

extern ::gostd::Ptr<RangeTable> Inscriptional_Pahlavi;

extern ::gostd::Ptr<RangeTable> Inscriptional_Parthian;

::gostd::Bool Is(::gostd::Ptr<RangeTable> rangeTab, ::gostd::Rune r);

::gostd::Bool IsOneOf(::gostd::Slice<::gostd::Ptr<RangeTable>> ranges, ::gostd::Rune r);

extern ::gostd::Ptr<RangeTable> Javanese;

extern ::gostd::Ptr<RangeTable> Join_Control;

extern ::gostd::Ptr<RangeTable> Kaithi;

extern ::gostd::Ptr<RangeTable> Kannada;

extern ::gostd::Ptr<RangeTable> Katakana;

extern ::gostd::Ptr<RangeTable> Kayah_Li;

extern ::gostd::Ptr<RangeTable> Kharoshthi;

extern ::gostd::Ptr<RangeTable> Khmer;

extern ::gostd::Ptr<RangeTable> Khojki;

extern ::gostd::Ptr<RangeTable> Khudawadi;

extern ::gostd::Ptr<RangeTable> L;

extern ::gostd::Ptr<RangeTable> Lao;

extern ::gostd::Ptr<RangeTable> Latin;

extern ::gostd::Ptr<RangeTable> Lepcha;

extern ::gostd::Ptr<RangeTable> Letter;

extern ::gostd::Ptr<RangeTable> Limbu;

extern ::gostd::Ptr<RangeTable> Linear_A;

extern ::gostd::Ptr<RangeTable> Linear_B;

extern ::gostd::Ptr<RangeTable> Lisu;

extern ::gostd::Ptr<RangeTable> Ll;

extern ::gostd::Ptr<RangeTable> Lm;

extern ::gostd::Ptr<RangeTable> Lo;

extern ::gostd::Ptr<RangeTable> Logical_Order_Exception;

extern ::gostd::Ptr<RangeTable> Lower;

extern ::gostd::Ptr<RangeTable> Lt;

extern ::gostd::Ptr<RangeTable> Lu;

extern ::gostd::Ptr<RangeTable> Lycian;

extern ::gostd::Ptr<RangeTable> Lydian;

extern ::gostd::Ptr<RangeTable> M;

extern ::gostd::Ptr<RangeTable> Mahajani;

extern ::gostd::Ptr<RangeTable> Malayalam;

extern ::gostd::Ptr<RangeTable> Mandaic;

extern ::gostd::Ptr<RangeTable> Manichaean;

extern ::gostd::Ptr<RangeTable> Marchen;

extern ::gostd::Ptr<RangeTable> Mark;

extern ::gostd::Ptr<RangeTable> Mc;

extern ::gostd::Ptr<RangeTable> Me;

extern ::gostd::Ptr<RangeTable> Meetei_Mayek;

extern ::gostd::Ptr<RangeTable> Mende_Kikakui;

extern ::gostd::Ptr<RangeTable> Meroitic_Cursive;

extern ::gostd::Ptr<RangeTable> Meroitic_Hieroglyphs;

extern ::gostd::Ptr<RangeTable> Miao;

extern ::gostd::Ptr<RangeTable> Mn;

extern ::gostd::Ptr<RangeTable> Modi;

extern ::gostd::Ptr<RangeTable> Mongolian;

extern ::gostd::Ptr<RangeTable> Mro;

extern ::gostd::Ptr<RangeTable> Multani;

extern ::gostd::Ptr<RangeTable> Myanmar;

extern ::gostd::Ptr<RangeTable> N;

extern ::gostd::Ptr<RangeTable> Nabataean;

extern ::gostd::Ptr<RangeTable> Nd;

extern ::gostd::Ptr<RangeTable> New_Tai_Lue;

extern ::gostd::Ptr<RangeTable> Newa;

extern ::gostd::Ptr<RangeTable> Nko;

extern ::gostd::Ptr<RangeTable> Nl;

extern ::gostd::Ptr<RangeTable> No;

extern ::gostd::Ptr<RangeTable> Noncharacter_Code_Point;

extern ::gostd::Ptr<RangeTable> Number;

extern ::gostd::Ptr<RangeTable> Ogham;

extern ::gostd::Ptr<RangeTable> Ol_Chiki;

extern ::gostd::Ptr<RangeTable> Old_Hungarian;

extern ::gostd::Ptr<RangeTable> Old_Italic;

extern ::gostd::Ptr<RangeTable> Old_North_Arabian;

extern ::gostd::Ptr<RangeTable> Old_Permic;

extern ::gostd::Ptr<RangeTable> Old_Persian;

extern ::gostd::Ptr<RangeTable> Old_South_Arabian;

extern ::gostd::Ptr<RangeTable> Old_Turkic;

extern ::gostd::Ptr<RangeTable> Oriya;

extern ::gostd::Ptr<RangeTable> Osage;

extern ::gostd::Ptr<RangeTable> Osmanya;

extern ::gostd::Ptr<RangeTable> Other;

extern ::gostd::Ptr<RangeTable> Other_Alphabetic;

extern ::gostd::Ptr<RangeTable> Other_Default_Ignorable_Code_Point;

extern ::gostd::Ptr<RangeTable> Other_Grapheme_Extend;

extern ::gostd::Ptr<RangeTable> Other_ID_Continue;

extern ::gostd::Ptr<RangeTable> Other_ID_Start;

extern ::gostd::Ptr<RangeTable> Other_Lowercase;

extern ::gostd::Ptr<RangeTable> Other_Math;

extern ::gostd::Ptr<RangeTable> Other_Uppercase;

extern ::gostd::Ptr<RangeTable> P;

extern ::gostd::Ptr<RangeTable> Pahawh_Hmong;

extern ::gostd::Ptr<RangeTable> Palmyrene;

extern ::gostd::Ptr<RangeTable> Pattern_Syntax;

extern ::gostd::Ptr<RangeTable> Pattern_White_Space;

extern ::gostd::Ptr<RangeTable> Pau_Cin_Hau;

extern ::gostd::Ptr<RangeTable> Pc;

extern ::gostd::Ptr<RangeTable> Pd;

extern ::gostd::Ptr<RangeTable> Pe;

extern ::gostd::Ptr<RangeTable> Pf;

extern ::gostd::Ptr<RangeTable> Phags_Pa;

extern ::gostd::Ptr<RangeTable> Phoenician;

extern ::gostd::Ptr<RangeTable> Pi;

extern ::gostd::Ptr<RangeTable> Po;

extern ::gostd::Ptr<RangeTable> Prepended_Concatenation_Mark;

extern ::gostd::Slice<::gostd::Ptr<RangeTable>> PrintRanges;

extern ::gostd::Map<::gostd::String, ::gostd::Ptr<RangeTable>> Properties;

extern ::gostd::Ptr<RangeTable> Ps;

extern ::gostd::Ptr<RangeTable> Psalter_Pahlavi;

extern ::gostd::Ptr<RangeTable> Punct;

extern ::gostd::Ptr<RangeTable> Quotation_Mark;

extern ::gostd::Ptr<RangeTable> Radical;

extern ::gostd::Ptr<RangeTable> Rejang;

constexpr auto ReplacementChar = ::gostd::UntypedConstant(65533);

extern ::gostd::Ptr<RangeTable> Runic;

extern ::gostd::Ptr<RangeTable> S;

extern ::gostd::Ptr<RangeTable> STerm;

extern ::gostd::Ptr<RangeTable> Samaritan;

extern ::gostd::Ptr<RangeTable> Saurashtra;

extern ::gostd::Ptr<RangeTable> Sc;

extern ::gostd::Map<::gostd::String, ::gostd::Ptr<RangeTable>> Scripts;

extern ::gostd::Ptr<RangeTable> Sentence_Terminal;

extern ::gostd::Ptr<RangeTable> Sharada;

extern ::gostd::Ptr<RangeTable> Shavian;

extern ::gostd::Ptr<RangeTable> Siddham;

extern ::gostd::Ptr<RangeTable> SignWriting;

::gostd::Rune SimpleFold(::gostd::Rune r);

extern ::gostd::Ptr<RangeTable> Sinhala;

extern ::gostd::Ptr<RangeTable> Sk;

extern ::gostd::Ptr<RangeTable> Sm;

extern ::gostd::Ptr<RangeTable> So;

extern ::gostd::Ptr<RangeTable> Soft_Dotted;

extern ::gostd::Ptr<RangeTable> Sora_Sompeng;

extern ::gostd::Ptr<RangeTable> Space;

extern ::gostd::Ptr<RangeTable> Sundanese;

extern ::gostd::Ptr<RangeTable> Syloti_Nagri;

extern ::gostd::Ptr<RangeTable> Symbol;

extern ::gostd::Ptr<RangeTable> Syriac;

extern ::gostd::Ptr<RangeTable> Tagalog;

extern ::gostd::Ptr<RangeTable> Tagbanwa;

extern ::gostd::Ptr<RangeTable> Tai_Le;

extern ::gostd::Ptr<RangeTable> Tai_Tham;

extern ::gostd::Ptr<RangeTable> Tai_Viet;

extern ::gostd::Ptr<RangeTable> Takri;

extern ::gostd::Ptr<RangeTable> Tamil;

extern ::gostd::Ptr<RangeTable> Tangut;

extern ::gostd::Ptr<RangeTable> Telugu;

extern ::gostd::Ptr<RangeTable> Terminal_Punctuation;

extern ::gostd::Ptr<RangeTable> Thaana;

extern ::gostd::Ptr<RangeTable> Thai;

extern ::gostd::Ptr<RangeTable> Tibetan;

extern ::gostd::Ptr<RangeTable> Tifinagh;

extern ::gostd::Ptr<RangeTable> Tirhuta;

extern ::gostd::Ptr<RangeTable> Title;

constexpr auto TitleCase = ::gostd::UntypedConstant(2);

::gostd::Rune To(::gostd::Int _case, ::gostd::Rune r);

::gostd::Rune ToLower(::gostd::Rune r);

::gostd::Rune ToTitle(::gostd::Rune r);

::gostd::Rune ToUpper(::gostd::Rune r);

extern ::gostd::Ptr<RangeTable> Ugaritic;

extern ::gostd::Ptr<RangeTable> Unified_Ideograph;

extern ::gostd::Ptr<RangeTable> Upper;

constexpr auto UpperCase = ::gostd::UntypedConstant(0);

constexpr auto UpperLower = ::gostd::UntypedConstant((MaxRune+1));

extern ::gostd::Ptr<RangeTable> Vai;

extern ::gostd::Ptr<RangeTable> Variation_Selector;

constexpr auto Version = ::gostd::UntypedConstant("9.0.0");

extern ::gostd::Ptr<RangeTable> Warang_Citi;

extern ::gostd::Ptr<RangeTable> White_Space;

extern ::gostd::Ptr<RangeTable> Yi;

extern ::gostd::Ptr<RangeTable> Z;

extern ::gostd::Ptr<RangeTable> Zl;

extern ::gostd::Ptr<RangeTable> Zp;

extern ::gostd::Ptr<RangeTable> Zs;

extern ::gostd::Ptr<RangeTable> _ASCII_Hex_Digit;

extern ::gostd::Ptr<RangeTable> _Adlam;

extern ::gostd::Ptr<RangeTable> _Ahom;

extern ::gostd::Ptr<RangeTable> _Anatolian_Hieroglyphs;

extern ::gostd::Ptr<RangeTable> _Arabic;

extern ::gostd::Ptr<RangeTable> _Armenian;

extern ::gostd::Ptr<RangeTable> _Avestan;

extern ::gostd::Ptr<RangeTable> _Balinese;

extern ::gostd::Ptr<RangeTable> _Bamum;

extern ::gostd::Ptr<RangeTable> _Bassa_Vah;

extern ::gostd::Ptr<RangeTable> _Batak;

extern ::gostd::Ptr<RangeTable> _Bengali;

extern ::gostd::Ptr<RangeTable> _Bhaiksuki;

extern ::gostd::Ptr<RangeTable> _Bidi_Control;

extern ::gostd::Ptr<RangeTable> _Bopomofo;

extern ::gostd::Ptr<RangeTable> _Brahmi;

extern ::gostd::Ptr<RangeTable> _Braille;

extern ::gostd::Ptr<RangeTable> _Buginese;

extern ::gostd::Ptr<RangeTable> _Buhid;

extern ::gostd::Ptr<RangeTable> _C;

extern ::gostd::Ptr<RangeTable> _Canadian_Aboriginal;

extern ::gostd::Ptr<RangeTable> _Carian;

extern ::gostd::Ptr<RangeTable> _Caucasian_Albanian;

extern ::gostd::Ptr<RangeTable> _Cc;

extern ::gostd::Ptr<RangeTable> _Cf;

extern ::gostd::Ptr<RangeTable> _Chakma;

extern ::gostd::Ptr<RangeTable> _Cham;

extern ::gostd::Ptr<RangeTable> _Cherokee;

extern ::gostd::Ptr<RangeTable> _Co;

extern ::gostd::Ptr<RangeTable> _Common;

extern ::gostd::Ptr<RangeTable> _Coptic;

extern ::gostd::Ptr<RangeTable> _Cs;

extern ::gostd::Ptr<RangeTable> _Cuneiform;

extern ::gostd::Ptr<RangeTable> _Cypriot;

extern ::gostd::Ptr<RangeTable> _Cyrillic;

extern ::gostd::Ptr<RangeTable> _Dash;

extern ::gostd::Ptr<RangeTable> _Deprecated;

extern ::gostd::Ptr<RangeTable> _Deseret;

extern ::gostd::Ptr<RangeTable> _Devanagari;

extern ::gostd::Ptr<RangeTable> _Diacritic;

extern ::gostd::Ptr<RangeTable> _Duployan;

extern ::gostd::Ptr<RangeTable> _Egyptian_Hieroglyphs;

extern ::gostd::Ptr<RangeTable> _Elbasan;

extern ::gostd::Ptr<RangeTable> _Ethiopic;

extern ::gostd::Ptr<RangeTable> _Extender;

extern ::gostd::Ptr<RangeTable> _Georgian;

extern ::gostd::Ptr<RangeTable> _Glagolitic;

extern ::gostd::Ptr<RangeTable> _Gothic;

extern ::gostd::Ptr<RangeTable> _Grantha;

extern ::gostd::Ptr<RangeTable> _Greek;

extern ::gostd::Ptr<RangeTable> _Gujarati;

extern ::gostd::Ptr<RangeTable> _Gurmukhi;

extern ::gostd::Ptr<RangeTable> _Han;

extern ::gostd::Ptr<RangeTable> _Hangul;

extern ::gostd::Ptr<RangeTable> _Hanunoo;

extern ::gostd::Ptr<RangeTable> _Hatran;

extern ::gostd::Ptr<RangeTable> _Hebrew;

extern ::gostd::Ptr<RangeTable> _Hex_Digit;

extern ::gostd::Ptr<RangeTable> _Hiragana;

extern ::gostd::Ptr<RangeTable> _Hyphen;

extern ::gostd::Ptr<RangeTable> _IDS_Binary_Operator;

extern ::gostd::Ptr<RangeTable> _IDS_Trinary_Operator;

extern ::gostd::Ptr<RangeTable> _Ideographic;

extern ::gostd::Ptr<RangeTable> _Imperial_Aramaic;

extern ::gostd::Ptr<RangeTable> _Inherited;

extern ::gostd::Ptr<RangeTable> _Inscriptional_Pahlavi;

extern ::gostd::Ptr<RangeTable> _Inscriptional_Parthian;

extern ::gostd::Ptr<RangeTable> _Javanese;

extern ::gostd::Ptr<RangeTable> _Join_Control;

extern ::gostd::Ptr<RangeTable> _Kaithi;

extern ::gostd::Ptr<RangeTable> _Kannada;

extern ::gostd::Ptr<RangeTable> _Katakana;

extern ::gostd::Ptr<RangeTable> _Kayah_Li;

extern ::gostd::Ptr<RangeTable> _Kharoshthi;

extern ::gostd::Ptr<RangeTable> _Khmer;

extern ::gostd::Ptr<RangeTable> _Khojki;

extern ::gostd::Ptr<RangeTable> _Khudawadi;

extern ::gostd::Ptr<RangeTable> _L;

extern ::gostd::Ptr<RangeTable> _Lao;

extern ::gostd::Ptr<RangeTable> _Latin;

extern ::gostd::Ptr<RangeTable> _Lepcha;

extern ::gostd::Ptr<RangeTable> _Limbu;

extern ::gostd::Ptr<RangeTable> _Linear_A;

extern ::gostd::Ptr<RangeTable> _Linear_B;

extern ::gostd::Ptr<RangeTable> _Lisu;

extern ::gostd::Ptr<RangeTable> _Ll;

extern ::gostd::Ptr<RangeTable> _Lm;

extern ::gostd::Ptr<RangeTable> _Lo;

extern ::gostd::Ptr<RangeTable> _Logical_Order_Exception;

extern ::gostd::Ptr<RangeTable> _Lt;

extern ::gostd::Ptr<RangeTable> _Lu;

extern ::gostd::Ptr<RangeTable> _Lycian;

extern ::gostd::Ptr<RangeTable> _Lydian;

extern ::gostd::Ptr<RangeTable> _M;

extern ::gostd::Ptr<RangeTable> _Mahajani;

extern ::gostd::Ptr<RangeTable> _Malayalam;

extern ::gostd::Ptr<RangeTable> _Mandaic;

extern ::gostd::Ptr<RangeTable> _Manichaean;

extern ::gostd::Ptr<RangeTable> _Marchen;

extern ::gostd::Ptr<RangeTable> _Mc;

extern ::gostd::Ptr<RangeTable> _Me;

extern ::gostd::Ptr<RangeTable> _Meetei_Mayek;

extern ::gostd::Ptr<RangeTable> _Mende_Kikakui;

extern ::gostd::Ptr<RangeTable> _Meroitic_Cursive;

extern ::gostd::Ptr<RangeTable> _Meroitic_Hieroglyphs;

extern ::gostd::Ptr<RangeTable> _Miao;

extern ::gostd::Ptr<RangeTable> _Mn;

extern ::gostd::Ptr<RangeTable> _Modi;

extern ::gostd::Ptr<RangeTable> _Mongolian;

extern ::gostd::Ptr<RangeTable> _Mro;

extern ::gostd::Ptr<RangeTable> _Multani;

extern ::gostd::Ptr<RangeTable> _Myanmar;

extern ::gostd::Ptr<RangeTable> _N;

extern ::gostd::Ptr<RangeTable> _Nabataean;

extern ::gostd::Ptr<RangeTable> _Nd;

extern ::gostd::Ptr<RangeTable> _New_Tai_Lue;

extern ::gostd::Ptr<RangeTable> _Newa;

extern ::gostd::Ptr<RangeTable> _Nko;

extern ::gostd::Ptr<RangeTable> _Nl;

extern ::gostd::Ptr<RangeTable> _No;

extern ::gostd::Ptr<RangeTable> _Noncharacter_Code_Point;

extern ::gostd::Ptr<RangeTable> _Ogham;

extern ::gostd::Ptr<RangeTable> _Ol_Chiki;

extern ::gostd::Ptr<RangeTable> _Old_Hungarian;

extern ::gostd::Ptr<RangeTable> _Old_Italic;

extern ::gostd::Ptr<RangeTable> _Old_North_Arabian;

extern ::gostd::Ptr<RangeTable> _Old_Permic;

extern ::gostd::Ptr<RangeTable> _Old_Persian;

extern ::gostd::Ptr<RangeTable> _Old_South_Arabian;

extern ::gostd::Ptr<RangeTable> _Old_Turkic;

extern ::gostd::Ptr<RangeTable> _Oriya;

extern ::gostd::Ptr<RangeTable> _Osage;

extern ::gostd::Ptr<RangeTable> _Osmanya;

extern ::gostd::Ptr<RangeTable> _Other_Alphabetic;

extern ::gostd::Ptr<RangeTable> _Other_Default_Ignorable_Code_Point;

extern ::gostd::Ptr<RangeTable> _Other_Grapheme_Extend;

extern ::gostd::Ptr<RangeTable> _Other_ID_Continue;

extern ::gostd::Ptr<RangeTable> _Other_ID_Start;

extern ::gostd::Ptr<RangeTable> _Other_Lowercase;

extern ::gostd::Ptr<RangeTable> _Other_Math;

extern ::gostd::Ptr<RangeTable> _Other_Uppercase;

extern ::gostd::Ptr<RangeTable> _P;

extern ::gostd::Ptr<RangeTable> _Pahawh_Hmong;

extern ::gostd::Ptr<RangeTable> _Palmyrene;

extern ::gostd::Ptr<RangeTable> _Pattern_Syntax;

extern ::gostd::Ptr<RangeTable> _Pattern_White_Space;

extern ::gostd::Ptr<RangeTable> _Pau_Cin_Hau;

extern ::gostd::Ptr<RangeTable> _Pc;

extern ::gostd::Ptr<RangeTable> _Pd;

extern ::gostd::Ptr<RangeTable> _Pe;

extern ::gostd::Ptr<RangeTable> _Pf;

extern ::gostd::Ptr<RangeTable> _Phags_Pa;

extern ::gostd::Ptr<RangeTable> _Phoenician;

extern ::gostd::Ptr<RangeTable> _Pi;

extern ::gostd::Ptr<RangeTable> _Po;

extern ::gostd::Ptr<RangeTable> _Prepended_Concatenation_Mark;

extern ::gostd::Ptr<RangeTable> _Ps;

extern ::gostd::Ptr<RangeTable> _Psalter_Pahlavi;

extern ::gostd::Ptr<RangeTable> _Quotation_Mark;

extern ::gostd::Ptr<RangeTable> _Radical;

extern ::gostd::Ptr<RangeTable> _Rejang;

extern ::gostd::Ptr<RangeTable> _Runic;

extern ::gostd::Ptr<RangeTable> _S;

extern ::gostd::Ptr<RangeTable> _Samaritan;

extern ::gostd::Ptr<RangeTable> _Saurashtra;

extern ::gostd::Ptr<RangeTable> _Sc;

extern ::gostd::Ptr<RangeTable> _Sentence_Terminal;

extern ::gostd::Ptr<RangeTable> _Sharada;

extern ::gostd::Ptr<RangeTable> _Shavian;

extern ::gostd::Ptr<RangeTable> _Siddham;

extern ::gostd::Ptr<RangeTable> _SignWriting;

extern ::gostd::Ptr<RangeTable> _Sinhala;

extern ::gostd::Ptr<RangeTable> _Sk;

extern ::gostd::Ptr<RangeTable> _Sm;

extern ::gostd::Ptr<RangeTable> _So;

extern ::gostd::Ptr<RangeTable> _Soft_Dotted;

extern ::gostd::Ptr<RangeTable> _Sora_Sompeng;

extern ::gostd::Ptr<RangeTable> _Sundanese;

extern ::gostd::Ptr<RangeTable> _Syloti_Nagri;

extern ::gostd::Ptr<RangeTable> _Syriac;

extern ::gostd::Ptr<RangeTable> _Tagalog;

extern ::gostd::Ptr<RangeTable> _Tagbanwa;

extern ::gostd::Ptr<RangeTable> _Tai_Le;

extern ::gostd::Ptr<RangeTable> _Tai_Tham;

extern ::gostd::Ptr<RangeTable> _Tai_Viet;

extern ::gostd::Ptr<RangeTable> _Takri;

extern ::gostd::Ptr<RangeTable> _Tamil;

extern ::gostd::Ptr<RangeTable> _Tangut;

extern ::gostd::Ptr<RangeTable> _Telugu;

extern ::gostd::Ptr<RangeTable> _Terminal_Punctuation;

extern ::gostd::Ptr<RangeTable> _Thaana;

extern ::gostd::Ptr<RangeTable> _Thai;

extern ::gostd::Ptr<RangeTable> _Tibetan;

extern ::gostd::Ptr<RangeTable> _Tifinagh;

extern ::gostd::Ptr<RangeTable> _Tirhuta;

extern ::gostd::Ptr<RangeTable> _Ugaritic;

extern ::gostd::Ptr<RangeTable> _Unified_Ideograph;

extern ::gostd::Ptr<RangeTable> _Vai;

extern ::gostd::Ptr<RangeTable> _Variation_Selector;

extern ::gostd::Ptr<RangeTable> _Warang_Citi;

extern ::gostd::Ptr<RangeTable> _White_Space;

extern ::gostd::Ptr<RangeTable> _Yi;

extern ::gostd::Ptr<RangeTable> _Z;

extern ::gostd::Ptr<RangeTable> _Zl;

extern ::gostd::Ptr<RangeTable> _Zp;

extern ::gostd::Ptr<RangeTable> _Zs;

extern ::gostd::Array<::gostd::Uint16, 128> asciiFold;

struct d : ::gostd::Array<::gostd::Rune, 3> {
    template <typename... Args> explicit d(Args&&... args) : ::gostd::Array<::gostd::Rune, 3>(cpp::forward<Args>(args)...) {}
};

struct CaseRange {
    ::gostd::Uint32 Lo;
    ::gostd::Uint32 Hi;
    d Delta;
};

extern ::gostd::Slice<CaseRange> CaseRanges;

struct SpecialCase : ::gostd::Slice<CaseRange> {
    ::gostd::Rune ToUpper(::gostd::Rune r);
    ::gostd::Rune ToTitle(::gostd::Rune r);
    ::gostd::Rune ToLower(::gostd::Rune r);
    template <typename... Args> explicit SpecialCase(Args&&... args) : ::gostd::Slice<CaseRange>(cpp::forward<Args>(args)...) {}
};

extern SpecialCase AzeriCase;

extern SpecialCase TurkishCase;

extern ::gostd::Slice<CaseRange> _CaseRanges;

extern SpecialCase _TurkishCase;

extern ::gostd::Ptr<RangeTable> foldCommon;

extern ::gostd::Ptr<RangeTable> foldGreek;

extern ::gostd::Ptr<RangeTable> foldInherited;

extern ::gostd::Ptr<RangeTable> foldL;

extern ::gostd::Ptr<RangeTable> foldLl;

extern ::gostd::Ptr<RangeTable> foldLt;

extern ::gostd::Ptr<RangeTable> foldLu;

extern ::gostd::Ptr<RangeTable> foldM;

extern ::gostd::Ptr<RangeTable> foldMn;

struct foldPair {
    ::gostd::Uint16 From;
    ::gostd::Uint16 To;
};

extern ::gostd::Slice<foldPair> caseOrbit;

::gostd::Bool is16(::gostd::Slice<Range16> ranges, ::gostd::Uint16 r);

::gostd::Bool is32(::gostd::Slice<Range32> ranges, ::gostd::Uint32 r);

::gostd::Bool isExcludingLatin(::gostd::Ptr<RangeTable> rangeTab, ::gostd::Rune r);

constexpr auto linearMax = ::gostd::UntypedConstant(18);

constexpr auto pC = ::gostd::UntypedConstant((1<<0));

constexpr auto pLl = ::gostd::UntypedConstant((1<<6));

constexpr auto pLu = ::gostd::UntypedConstant((1<<5));

constexpr auto pLo = ::gostd::UntypedConstant((pLl|pLu));

constexpr auto pLmask = ::gostd::UntypedConstant(pLo);

constexpr auto pN = ::gostd::UntypedConstant((1<<2));

constexpr auto pP = ::gostd::UntypedConstant((1<<1));

constexpr auto pS = ::gostd::UntypedConstant((1<<3));

constexpr auto pZ = ::gostd::UntypedConstant((1<<4));

constexpr auto pp = ::gostd::UntypedConstant((1<<7));

constexpr auto pg = ::gostd::UntypedConstant((pp|pZ));

extern ::gostd::Array<::gostd::Uint8, 256> properties;

::gostd::Rune to(::gostd::Int _case, ::gostd::Rune r, ::gostd::Slice<CaseRange> caseRange);

}

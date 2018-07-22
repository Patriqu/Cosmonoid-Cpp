<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en-US" lang="en-US">
<head>
<link rel="icon" href="/SDL/static/hgicon.png" type="image/png" />
<meta name="robots" content="index, nofollow"/>
<link rel="stylesheet" href="/SDL/static/style-gitweb.css" type="text/css" />
<script type="text/javascript" src="/SDL/static/mercurial.js"></script>

<title>SDL: include/SDL_timer.h@8f71b590aff6</title>
<link rel="alternate" type="application/atom+xml"
   href="/SDL/atom-log" title="Atom feed for SDL"/>
<link rel="alternate" type="application/rss+xml"
   href="/SDL/rss-log" title="RSS feed for SDL"/>
</head>
<body>

<div class="page_header">
<a href="http://mercurial.selenic.com/" title="Mercurial" style="float: right;">Mercurial</a><a href="/SDL/summary">SDL</a> / file revision
</div>

<div class="page_nav">
<a href="/SDL/summary">summary</a> |
<a href="/SDL/shortlog">shortlog</a> |
<a href="/SDL/log">changelog</a> |
<a href="/SDL/graph">graph</a> |
<a href="/SDL/tags">tags</a> |
<a href="/SDL/bookmarks">bookmarks</a> |
<a href="/SDL/branches">branches</a> |
<a href="/SDL/file/8f71b590aff6/include/">files</a> |
<a href="/SDL/rev/8f71b590aff6">changeset</a> |
file |
<a href="/SDL/file/tip/include/SDL_timer.h">latest</a> |
<a href="/SDL/log/8f71b590aff6/include/SDL_timer.h">revisions</a> |
<a href="/SDL/annotate/8f71b590aff6/include/SDL_timer.h">annotate</a> |
<a href="/SDL/diff/8f71b590aff6/include/SDL_timer.h">diff</a> |
<a href="/SDL/raw-file/8f71b590aff6/include/SDL_timer.h">raw</a> |
<a href="/SDL/help">help</a>
<br/>
</div>

<div class="title">include/SDL_timer.h</div>

<div class="title_text">
<table cellspacing="0">
<tr>
 <td>author</td>
 <td>&#80;&#104;&#105;&#108;&#105;&#112;&#112;&#32;&#87;&#105;&#101;&#115;&#101;&#109;&#97;&#110;&#110;&#32;&#60;&#112;&#104;&#105;&#108;&#105;&#112;&#112;&#46;&#119;&#105;&#101;&#115;&#101;&#109;&#97;&#110;&#110;&#64;&#97;&#114;&#99;&#111;&#114;&#46;&#100;&#101;&#62;</td></tr>
<tr>
 <td></td>
 <td class="date age">Sun, 18 Aug 2013 11:15:30 +0200</td></tr>

<tr>
 <td>changeset 7655</td>
 <td style="font-family:monospace"><a class="list" href="/SDL/rev/8f71b590aff6">8f71b590aff6</a></td></tr>

<tr>
<td>parent 6885</td>
<td style="font-family:monospace">
<a class="list" href="/SDL/file/700f1b25f77f/include/SDL_timer.h">
700f1b25f77f
</a>
</td>
</tr>

<tr>
 <td>permissions</td>
 <td style="font-family:monospace">-rw-r--r--</td></tr>
</table>
</div>

<div class="page_path">
Replaced introduction in header file with more recent version from README.txt.
</div>

<div class="page_body">

<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l1" id="l1">     1</a> /*
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l2" id="l2">     2</a>   Simple DirectMedia Layer
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l3" id="l3">     3</a>   Copyright (C) 1997-2013 Sam Lantinga &lt;slouken@libsdl.org&gt;
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l4" id="l4">     4</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l5" id="l5">     5</a>   This software is provided 'as-is', without any express or implied
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l6" id="l6">     6</a>   warranty.  In no event will the authors be held liable for any damages
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l7" id="l7">     7</a>   arising from the use of this software.
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l8" id="l8">     8</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l9" id="l9">     9</a>   Permission is granted to anyone to use this software for any purpose,
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l10" id="l10">    10</a>   including commercial applications, and to alter it and redistribute it
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l11" id="l11">    11</a>   freely, subject to the following restrictions:
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l12" id="l12">    12</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l13" id="l13">    13</a>   1. The origin of this software must not be misrepresented; you must not
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l14" id="l14">    14</a>      claim that you wrote the original software. If you use this software
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l15" id="l15">    15</a>      in a product, an acknowledgment in the product documentation would be
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l16" id="l16">    16</a>      appreciated but is not required.
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l17" id="l17">    17</a>   2. Altered source versions must be plainly marked as such, and must not be
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l18" id="l18">    18</a>      misrepresented as being the original software.
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l19" id="l19">    19</a>   3. This notice may not be removed or altered from any source distribution.
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l20" id="l20">    20</a> */
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l21" id="l21">    21</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l22" id="l22">    22</a> #ifndef _SDL_timer_h
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l23" id="l23">    23</a> #define _SDL_timer_h
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l24" id="l24">    24</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l25" id="l25">    25</a> /**
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l26" id="l26">    26</a>  *  \file SDL_timer.h
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l27" id="l27">    27</a>  *
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l28" id="l28">    28</a>  *  Header for the SDL time management routines.
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l29" id="l29">    29</a>  */
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l30" id="l30">    30</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l31" id="l31">    31</a> #include &quot;SDL_stdinc.h&quot;
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l32" id="l32">    32</a> #include &quot;SDL_error.h&quot;
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l33" id="l33">    33</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l34" id="l34">    34</a> #include &quot;begin_code.h&quot;
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l35" id="l35">    35</a> /* Set up for C function definitions, even when using C++ */
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l36" id="l36">    36</a> #ifdef __cplusplus
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l37" id="l37">    37</a> extern &quot;C&quot; {
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l38" id="l38">    38</a> #endif
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l39" id="l39">    39</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l40" id="l40">    40</a> /**
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l41" id="l41">    41</a>  * \brief Get the number of milliseconds since the SDL library initialization.
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l42" id="l42">    42</a>  *
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l43" id="l43">    43</a>  * \note This value wraps if the program runs for more than ~49 days.
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l44" id="l44">    44</a>  */
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l45" id="l45">    45</a> extern DECLSPEC Uint32 SDLCALL SDL_GetTicks(void);
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l46" id="l46">    46</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l47" id="l47">    47</a> /**
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l48" id="l48">    48</a>  * \brief Get the current value of the high resolution counter
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l49" id="l49">    49</a>  */
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l50" id="l50">    50</a> extern DECLSPEC Uint64 SDLCALL SDL_GetPerformanceCounter(void);
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l51" id="l51">    51</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l52" id="l52">    52</a> /**
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l53" id="l53">    53</a>  * \brief Get the count per second of the high resolution counter
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l54" id="l54">    54</a>  */
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l55" id="l55">    55</a> extern DECLSPEC Uint64 SDLCALL SDL_GetPerformanceFrequency(void);
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l56" id="l56">    56</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l57" id="l57">    57</a> /**
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l58" id="l58">    58</a>  * \brief Wait a specified number of milliseconds before returning.
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l59" id="l59">    59</a>  */
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l60" id="l60">    60</a> extern DECLSPEC void SDLCALL SDL_Delay(Uint32 ms);
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l61" id="l61">    61</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l62" id="l62">    62</a> /**
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l63" id="l63">    63</a>  *  Function prototype for the timer callback function.
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l64" id="l64">    64</a>  *
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l65" id="l65">    65</a>  *  The callback function is passed the current timer interval and returns
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l66" id="l66">    66</a>  *  the next timer interval.  If the returned value is the same as the one
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l67" id="l67">    67</a>  *  passed in, the periodic alarm continues, otherwise a new alarm is
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l68" id="l68">    68</a>  *  scheduled.  If the callback returns 0, the periodic alarm is cancelled.
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l69" id="l69">    69</a>  */
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l70" id="l70">    70</a> typedef Uint32 (SDLCALL * SDL_TimerCallback) (Uint32 interval, void *param);
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l71" id="l71">    71</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l72" id="l72">    72</a> /**
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l73" id="l73">    73</a>  * Definition of the timer ID type.
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l74" id="l74">    74</a>  */
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l75" id="l75">    75</a> typedef int SDL_TimerID;
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l76" id="l76">    76</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l77" id="l77">    77</a> /**
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l78" id="l78">    78</a>  * \brief Add a new timer to the pool of timers already running.
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l79" id="l79">    79</a>  *
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l80" id="l80">    80</a>  * \return A timer ID, or NULL when an error occurs.
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l81" id="l81">    81</a>  */
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l82" id="l82">    82</a> extern DECLSPEC SDL_TimerID SDLCALL SDL_AddTimer(Uint32 interval,
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l83" id="l83">    83</a>                                                  SDL_TimerCallback callback,
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l84" id="l84">    84</a>                                                  void *param);
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l85" id="l85">    85</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l86" id="l86">    86</a> /**
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l87" id="l87">    87</a>  * \brief Remove a timer knowing its ID.
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l88" id="l88">    88</a>  *
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l89" id="l89">    89</a>  * \return A boolean value indicating success or failure.
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l90" id="l90">    90</a>  *
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l91" id="l91">    91</a>  * \warning It is not safe to remove a timer multiple times.
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l92" id="l92">    92</a>  */
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l93" id="l93">    93</a> extern DECLSPEC SDL_bool SDLCALL SDL_RemoveTimer(SDL_TimerID id);
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l94" id="l94">    94</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l95" id="l95">    95</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l96" id="l96">    96</a> /* Ends C function definitions when using C++ */
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l97" id="l97">    97</a> #ifdef __cplusplus
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l98" id="l98">    98</a> }
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l99" id="l99">    99</a> #endif
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l100" id="l100">   100</a> #include &quot;close_code.h&quot;
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l101" id="l101">   101</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l102" id="l102">   102</a> #endif /* _SDL_timer_h */
</pre>
</div>
<div style="font-family:monospace" class="parity0">
<pre><a class="linenr" href="#l103" id="l103">   103</a> 
</pre>
</div>
<div style="font-family:monospace" class="parity1">
<pre><a class="linenr" href="#l104" id="l104">   104</a> /* vi: set ts=4 sw=4 expandtab: */
</pre>
</div>
</div>

<script type="text/javascript">process_dates()</script>
<div class="page_footer">
<div class="page_footer_text">SDL</div>
<div class="rss_logo">
<a href="/SDL/rss-log">RSS</a>
<a href="/SDL/atom-log">Atom</a>
</div>
<br />

</div>
</body>
</html>


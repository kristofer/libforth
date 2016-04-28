/** @file       libforth.h
 *  @brief      A FORTH library, based on <www.ioccc.org/1992/buzzard.2.c>
 *  @author     Richard James Howe.
 *  @copyright  Copyright 2015 Richard James Howe.
 *  @license    LGPL v2.1 or later version
 *  @email      howe.r.j.89@gmail.com 
 *  @todo       The library interface needs expanding so that it is more
 *              useful to programs utilizing this library. 
 *  @todo       An optional line-editing REPL, brought in from elsewhere
 *              would be nice, like "linenoise".
 *  @todo       Unit tests and assertions should be added for easy of
 *              maintenance. Better documentation and more example code
 *              should also be written.
 *  @todo       Portable core dump files and reading code in from blocks.
 *  @todo       A 32-bit version should be made, with the option of
 *              to set the initial core size used. **/
#ifndef FORTH_H
#define FORTH_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdint.h>
struct forth; /**< An opaque object that holds a running FORTH environment**/
typedef struct forth forth;
typedef uint16_t mw; /**< FORTH "machine word", basic int used.*/
/** @brief   Given an input and an output this will initialize forth,
 *           allocating memory for it and setting it up so it has a few
 *           FORTH words predefined. The returned object must be free'd
 *           by the caller and can be done with free(). It will return NULL
 *           on failure.
 *  @param   input       Read from this input file. Caller closes.
 *  @param   output      Output to this file. Caller closes.
 *  @return  forth A fully initialized forth environment or NULL. **/
forth *forth_init(FILE *input, FILE *output); 
/** @brief   Given a FORTH object it will free any memory and perform any
 *           internal cleanup needed. This will not free any evaluated
 *           strings nor will it close any files passed in via the C-API.
 *  @param   o    An object to free
 *  @return  void **/
void forth_free(forth *o); 
/** @brief   Execute an initialized forth environment, this will read
 *           from input until there is no more or an error occurs. If
 *           an error occurs a negative number will be returned and the
 *           forth object passed to forth_run will be invalidated, all
 *           subsequent calls to forth_run() or forth_eval() will return
 *           errors.
 *  @param   o   An initialized forth environment. Caller frees.
 *  @return  int This is an error code, less than one is an error. **/
int forth_run(forth *o); 
/** @brief   This function behaves like forth_run() but instead will
 *           read from a string until there is no more. It will like-
 *           wise invalidate objects if there is an error evaluating the
 *           string. Do not forget to call either forth_seti() or forth_seto(),
 *           or to close any previous files passed to forth_eval() after
 *           you have called forth_eval(). Multiple calls to forth_eval()
 *           will work however.
 *  @param   o   An initialized forth environment. Caller frees.
 *  @param   s   A NUL terminated string to read from.
 *  @return  int This is an error code, less than one is an error. **/
int forth_eval(forth *o, const char *s); 
/** @brief   Dump the opaque FORTH object to file, this is a raw dump
 *           of the object and any pointers it may or may not have at
 *           the time of the dump. The contents of this dump are not
 *           guaranteed to have any specific format or structure.
 *  @param   o    The FORTH environment to dump. Caller frees. Asserted.
 *  @param   dump Core dump file handle ("wb"). Caller closes. Asserted.
 *  @return  int  An error code, negative on error. **/
int forth_dump_core(forth *o, FILE *dump);
/** @brief Set the input of an environment 'o' to read from a file 'in'.
 *  @param o   An initialized FORTH environment. Caller frees.
 *  @param in  Open handle for reading; "r"/"rb". Caller closes. **/
void forth_set_file_input(forth *o, FILE *in);
/** @brief Set the output file of an environment 'o'.
 *  @param o   An initialized FORTH environment. Caller frees. Asserted.
 *  @param out Open handle for writing; "w"/"wb". Caller closes. Asserted. **/
void forth_set_file_output(forth *o, FILE *out);    
/** @brief Set the input of an environment 'o' to read from a string 's'.
 *  @param o   An initialized FORTH environment. Caller frees. Asserted.
 *  @param s   A NUL terminated string to act as input. Asserted. **/
void forth_set_string_input(forth *o, const char *s); 
/** @brief  This implements a FORTH REPL whose behavior is documented in
 *          the man pages for this library. You pass in the same format as
 *          is expected to main(). The only option possible to pass to argv
 *          is "-d" which automatically performs a forth_coredump() after
 *          it has read all the files passed in argv. All other strings
 *          are treated as file names to open and read input from. Consult
 *          the man pages.
 *  @param  argc  An argument count, like in main().
 *  @param  argv  argc strings, like in main(). Not checked for NULL.
 *  @return int   A error code. Anything non zero is an error. **/
int main_forth(int argc, char **argv); 
#ifdef __cplusplus
}
#endif
#endif

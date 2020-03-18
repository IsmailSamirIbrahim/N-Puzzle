
#ifndef N_PUZZLE_EXPORT_H
#define N_PUZZLE_EXPORT_H

#ifdef N_PUZZLE_STATIC_DEFINE
#  define N_PUZZLE_EXPORT
#  define N_PUZZLE_NO_EXPORT
#else
#  ifndef N_PUZZLE_EXPORT
#    ifdef n_puzzle_EXPORTS
        /* We are building this library */
#      define N_PUZZLE_EXPORT 
#    else
        /* We are using this library */
#      define N_PUZZLE_EXPORT 
#    endif
#  endif

#  ifndef N_PUZZLE_NO_EXPORT
#    define N_PUZZLE_NO_EXPORT 
#  endif
#endif

#ifndef N_PUZZLE_DEPRECATED
#  define N_PUZZLE_DEPRECATED __declspec(deprecated)
#endif

#ifndef N_PUZZLE_DEPRECATED_EXPORT
#  define N_PUZZLE_DEPRECATED_EXPORT N_PUZZLE_EXPORT N_PUZZLE_DEPRECATED
#endif

#ifndef N_PUZZLE_DEPRECATED_NO_EXPORT
#  define N_PUZZLE_DEPRECATED_NO_EXPORT N_PUZZLE_NO_EXPORT N_PUZZLE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef N_PUZZLE_NO_DEPRECATED
#    define N_PUZZLE_NO_DEPRECATED
#  endif
#endif

#endif /* N_PUZZLE_EXPORT_H */

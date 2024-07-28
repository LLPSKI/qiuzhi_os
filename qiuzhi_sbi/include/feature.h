#ifndef _FEATURE_H
#define _FEATURE_H

#ifndef MACHINE

#error No machine is founded!

#else

#if (MACHINE == VIRT)

#define VIRT

#elif (MACHINE == NEMU)

#endif /* (MACHINE == VIRT) */

#endif /* MACHINE */

#endif /* _FEATURE_H */
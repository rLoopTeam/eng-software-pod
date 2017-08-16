#ifndef _POD_H_
#define _POD_H_

#include "../COMPAT.h"
#include "pod__control.h"
#include "pod__types.h"


/**
 *  Pod Init
 */
void vPod__Init(strPod *sPod);

/**
 *  Process Pod
 */
void vPod__Process(strPod *sPod);


/**
 *  Pod 10MS ISR
 */
void vPod__10MS_ISR(strPod *sPod);

/**
 *  Pod 100MS ISR
 */
void vPod__100MS_ISR(strPod *sPod);


#endif // _POD_H_

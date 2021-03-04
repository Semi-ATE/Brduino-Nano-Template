/*
 * CmdSystem.h
 *
 *  Created on: Aug 12, 2020
 *      Author: martin
 */

#ifndef CMDSYSTEM_H_
#define CMDSYSTEM_H_

int InitSystemCommandHandler(void);
int SystemCommandHandler(int16_t dev_nr,uint8_t *command,int len);

#endif /* CMDSYSTEM_H_ */

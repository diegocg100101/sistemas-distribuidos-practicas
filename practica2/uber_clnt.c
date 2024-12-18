/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "uber.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

info_auto *
solicitar_viaje_1(posicion arg1,  CLIENT *clnt)
{
	static info_auto clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, solicitar_viaje,
		(xdrproc_t) xdr_posicion, (caddr_t) &arg1,
		(xdrproc_t) xdr_info_auto, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

void *
terminar_viaje_1(posicion arg1, double arg2, char *arg3,  CLIENT *clnt)
{
	terminar_viaje_1_argument arg;
	static char clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	arg.arg3 = arg3;
	if (clnt_call (clnt, terminar_viaje, (xdrproc_t) xdr_terminar_viaje_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_void, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return ((void *)&clnt_res);
}

info_servicio *
estado_servicio_1(CLIENT *clnt)
{
	static info_servicio clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	 if (clnt_call (clnt, estado_servicio, (xdrproc_t) xdr_void, (caddr_t) NULL,
		(xdrproc_t) xdr_info_servicio, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

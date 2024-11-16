/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "uber.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static info_auto *
_solicitar_viaje_1 (posicion  *argp, struct svc_req *rqstp)
{
	return (solicitar_viaje_1_svc(*argp, rqstp));
}

static void *
_terminar_viaje_1 (terminar_viaje_1_argument *argp, struct svc_req *rqstp)
{
	return (terminar_viaje_1_svc(argp->arg1, argp->arg2, argp->arg3, rqstp));
}

static info_servicio *
_estado_servicio_1 (void  *argp, struct svc_req *rqstp)
{
	return (estado_servicio_1_svc(rqstp));
}

static void
uber_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		posicion solicitar_viaje_1_arg;
		terminar_viaje_1_argument terminar_viaje_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case solicitar_viaje:
		_xdr_argument = (xdrproc_t) xdr_posicion;
		_xdr_result = (xdrproc_t) xdr_info_auto;
		local = (char *(*)(char *, struct svc_req *)) _solicitar_viaje_1;
		break;

	case terminar_viaje:
		_xdr_argument = (xdrproc_t) xdr_terminar_viaje_1_argument;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) _terminar_viaje_1;
		break;

	case estado_servicio:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_info_servicio;
		local = (char *(*)(char *, struct svc_req *)) _estado_servicio_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (UBER, UBER_VERSION);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, UBER, UBER_VERSION, uber_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (UBER, UBER_VERSION, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, UBER, UBER_VERSION, uber_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (UBER, UBER_VERSION, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
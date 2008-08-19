
#include <freewpc.h>
#include <queue.h>

#define HOST_BUFFER_SIZE 16

/* Queues the data from the sound board to the CPU board */
struct {
	U8 head;
	U8 tail;
	U8 elems[HOST_BUFFER_SIZE];
} host_write_queue;
#define host_write_args (queue_t *)&host_write_queue, HOST_BUFFER_SIZE


/* Queues the data from the CPU board to the sound board */
struct {
	U8 head;
	U8 tail;
	U8 elems[HOST_BUFFER_SIZE];
} host_read_queue;
#define host_read_args (queue_t *)&host_read_queue, HOST_BUFFER_SIZE


/** Receive a character from the host, and queue it for
later processing.  This is called only when there is
known to be a new character latched there, by way of
the IRQ line. */
void host_receive (void)
{
	queue_insert (host_read_args, readb (WPCS_HOST_INPUT));
}


/** Send a pending character back to the host. */
void host_send (void)
{
	if (!queue_empty_p ((queue_t *)&host_write_queue))
	{
		writeb (WPCS_HOST_OUTPUT, queue_remove (host_write_args));
	}
}


void host_write (U8 val)
{
	queue_insert (host_write_args, val);
}


U8 host_read (void)
{
	return queue_remove (host_read_args);
}


bool host_read_ready (void)
{
	return !queue_empty_p ((queue_t *)&host_read_queue);
}

void host_init (void)
{
	queue_init ((queue_t *)&host_write_queue);
	queue_init ((queue_t *)&host_read_queue);
}

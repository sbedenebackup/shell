/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sc_exec.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sbedene <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/04 21:06:24 by sbedene      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/04 21:06:25 by sbedene     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "sc_script.h"

t_kwqueue   *add_queue(t_kwqueue *queue, t_tree *node)
{
    t_kwqueue   *elem;

    elem = (t_kwqueue *)malloc(sizeof(t_kwqueue));
    elem->kw = node->kw;
    elem->node = node;
    if (queue)
        queue->next = elem;
    elem->prev = queue;
    return (elem);
}

void    sc_exec(t_script *script)
{
    t_tree      *node;
    t_kwqueue   *queue;

    node = script->tree;
    queue = NULL;
    while (node)
    {
        if (node->type == T_KW)
        {
            if (queue && is_new_cond(node->kw))
                queue = queue->prev;
            queue = add_queue(queue, node);
            node = node->true;
        }
        else if (node->type == T_INSTR)
        {
            printf("%s\n", node->instr);
            if (node->next && is_secondary_cond(node->next->kw))
            {
                node = queue->node->next;
                while (node && is_secondary_cond(node->kw))
                {
                    printf("A");
                    node = node->next;
                }
            }
            else
                node = node->next;
        }
    }
}
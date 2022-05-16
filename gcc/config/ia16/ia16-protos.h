/* GNU Compiler Collection prototypes for target machine Intel 16-bit x86.
   Copyright (C) 2005-2017 Free Software Foundation, Inc.
   Contributed by Rask Ingemann Lambertsen <rask@sygehus.dk>
   Changes by Andrew Jenner <andrew@codesourcery.com>
   Very preliminary IA-16 far pointer support by TK Chia

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it under the
   terms of the GNU General Public License as published by the Free Software
   Foundation; either version 3 of the License, or (at your option) any
   later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
   details.

   You should have received a copy of the GNU General Public License along
   with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

extern struct gcc_target targetm;
extern unsigned char	ia16_hard_regno_nregs[17][FIRST_PSEUDO_REGISTER];
extern enum reg_class const ia16_regno_class[FIRST_PSEUDO_REGISTER];
extern int		ia16_regno_in_class_p (unsigned, unsigned);
extern int		ia16_in_far_function_p (void);
extern bool		ia16_have_seg_override_p (rtx x);
extern HOST_WIDE_INT	ia16_first_parm_offset (tree fundecl);
extern HOST_WIDE_INT	ia16_initial_frame_pointer_offset (void);
extern HOST_WIDE_INT
		ia16_initial_elimination_offset (unsigned int from, unsigned int to);
extern enum machine_mode
		ia16_cc_modes_compatible (enum machine_mode mode1, enum machine_mode mode2);

extern rtx	ia16_expand_weird_pointer_plus_expr (rtx op0, rtx op1, rtx target,
						     machine_mode mode);
extern rtx	ia16_as_convert_weird_memory_address (machine_mode to_mode,
						      rtx x, addr_space_t as,
						      bool in_const, bool no_emit);
extern void	ia16_split_seg_override_and_offset (rtx x, rtx *ovr, rtx *off);

#ifdef RTX_CODE
extern void	ia16_initialize_trampoline (rtx addr, rtx fnaddr, rtx static_chain);
extern bool	ia16_parse_address (rtx e, rtx *p_r1, rtx *p_r2, rtx *p_c, rtx *p_r9);
extern void	ia16_print_operand (FILE *file, rtx x, int code);
extern void	ia16_print_operand_address (FILE *file, rtx x);
#endif
extern rtx	ia16_push_reg (unsigned int regno);
extern rtx	ia16_pop_reg (unsigned int regno);
#ifdef RTX_CODE
extern enum machine_mode
		ia16_select_cc_mode (enum rtx_code op, rtx x, rtx y, bool branch);
extern rtx	ia16_gen_compare_reg (enum rtx_code op, rtx x, rtx y, bool branch);
extern bool	ia16_arith_operands_p (enum rtx_code code, rtx *operands);
extern rtx	ia16_prepare_operands (enum rtx_code, rtx *operands);
extern bool	ia16_move_multiple_mem_p (enum machine_mode mode, rtx m1, rtx m2);
extern bool	ia16_move_multiple_reg_p (enum machine_mode mode, rtx r1, rtx r2);
extern bool	ia16_non_overlapping_mem_p (rtx m1, rtx m2);
#endif

extern void	ia16_expand_prologue (void);
extern void	ia16_expand_reset_ds_for_call (rtx addr);
extern void	ia16_expand_epilogue (bool sibcall);
extern const char *
		ia16_get_call_expansion (rtx, machine_mode, bool);
extern const char *
		ia16_get_sibcall_expansion (rtx, machine_mode, bool);
extern void	ia16_asm_output_addr_diff_elt (FILE *, rtx, int, int);
extern void	ia16_asm_output_addr_vec_elt (FILE *, int);

extern void	ia16_cpu_cpp_builtins (void);
extern void	ia16_register_pragmas (void);

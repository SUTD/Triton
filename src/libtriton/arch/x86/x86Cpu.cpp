//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <cstring>

#include <architecture.hpp>
#include <coreUtils.hpp>
#include <cpuSize.hpp>
#include <externalLibs.hpp>
#include <immediateOperand.hpp>
#include <x86Cpu.hpp>
#include <x86Specifications.hpp>

#ifdef TRITON_PYTHON_BINDINGS
  #include <pythonBindings.hpp>
#endif



namespace triton {
  namespace arch {
    namespace x86 {

      x86Cpu::x86Cpu() {
        this->clear();
      }


      x86Cpu::x86Cpu(const x86Cpu& other) {
        this->copy(other);
      }


      x86Cpu::~x86Cpu() {
        this->memory.clear();
      }


      void x86Cpu::copy(const x86Cpu& other) {
        this->memory = other.memory;
        memcpy(this->eax,     other.eax,    sizeof(this->eax));
        memcpy(this->ebx,     other.ebx,    sizeof(this->ebx));
        memcpy(this->ecx,     other.ecx,    sizeof(this->ecx));
        memcpy(this->edx,     other.edx,    sizeof(this->edx));
        memcpy(this->edi,     other.edi,    sizeof(this->edi));
        memcpy(this->esi,     other.esi,    sizeof(this->esi));
        memcpy(this->esp,     other.esp,    sizeof(this->esp));
        memcpy(this->ebp,     other.ebp,    sizeof(this->ebp));
        memcpy(this->eip,     other.eip,    sizeof(this->eip));
        memcpy(this->eflags,  other.eflags, sizeof(this->eflags));
        memcpy(this->mm0,     other.mm0,    sizeof(this->mm0));
        memcpy(this->mm1,     other.mm1,    sizeof(this->mm1));
        memcpy(this->mm2,     other.mm2,    sizeof(this->mm2));
        memcpy(this->mm3,     other.mm3,    sizeof(this->mm3));
        memcpy(this->mm4,     other.mm4,    sizeof(this->mm4));
        memcpy(this->mm5,     other.mm5,    sizeof(this->mm5));
        memcpy(this->mm6,     other.mm6,    sizeof(this->mm6));
        memcpy(this->mm7,     other.mm7,    sizeof(this->mm7));
        memcpy(this->xmm0,    other.xmm0,   sizeof(this->xmm0));
        memcpy(this->xmm1,    other.xmm1,   sizeof(this->xmm1));
        memcpy(this->xmm2,    other.xmm2,   sizeof(this->xmm2));
        memcpy(this->xmm3,    other.xmm3,   sizeof(this->xmm3));
        memcpy(this->xmm4,    other.xmm4,   sizeof(this->xmm4));
        memcpy(this->xmm5,    other.xmm5,   sizeof(this->xmm5));
        memcpy(this->xmm6,    other.xmm6,   sizeof(this->xmm6));
        memcpy(this->xmm7,    other.xmm7,   sizeof(this->xmm7));
        memcpy(this->ymm0,    other.ymm0,   sizeof(this->ymm0));
        memcpy(this->ymm1,    other.ymm1,   sizeof(this->ymm1));
        memcpy(this->ymm2,    other.ymm2,   sizeof(this->ymm2));
        memcpy(this->ymm3,    other.ymm3,   sizeof(this->ymm3));
        memcpy(this->ymm4,    other.ymm4,   sizeof(this->ymm4));
        memcpy(this->ymm5,    other.ymm5,   sizeof(this->ymm5));
        memcpy(this->ymm6,    other.ymm6,   sizeof(this->ymm6));
        memcpy(this->ymm7,    other.ymm7,   sizeof(this->ymm7));
        memcpy(this->mxcsr,   other.mxcsr,  sizeof(this->mxcsr));
        memcpy(this->cr0,     other.cr0,    sizeof(this->cr0));
        memcpy(this->cr1,     other.cr1,    sizeof(this->cr1));
        memcpy(this->cr2,     other.cr2,    sizeof(this->cr2));
        memcpy(this->cr3,     other.cr3,    sizeof(this->cr3));
        memcpy(this->cr4,     other.cr4,    sizeof(this->cr4));
        memcpy(this->cr5,     other.cr5,    sizeof(this->cr5));
        memcpy(this->cr6,     other.cr6,    sizeof(this->cr6));
        memcpy(this->cr7,     other.cr7,    sizeof(this->cr7));
        memcpy(this->cr8,     other.cr8,    sizeof(this->cr8));
        memcpy(this->cr9,     other.cr9,    sizeof(this->cr9));
        memcpy(this->cr10,    other.cr10,   sizeof(this->cr10));
        memcpy(this->cr11,    other.cr11,   sizeof(this->cr11));
        memcpy(this->cr12,    other.cr12,   sizeof(this->cr12));
        memcpy(this->cr13,    other.cr13,   sizeof(this->cr13));
        memcpy(this->cr14,    other.cr14,   sizeof(this->cr14));
        memcpy(this->cr15,    other.cr15,   sizeof(this->cr15));
        memcpy(this->cs,      other.cs,     sizeof(this->cs));
        memcpy(this->ds,      other.ds,     sizeof(this->ds));
        memcpy(this->es,      other.es,     sizeof(this->es));
        memcpy(this->fs,      other.fs,     sizeof(this->fs));
        memcpy(this->gs,      other.gs,     sizeof(this->gs));
        memcpy(this->ss,      other.ss,     sizeof(this->ss));
      }


      void x86Cpu::init(void) {
        /* Define registers ========================================================= */
        triton::arch::x86::x86_reg_rax    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_eax    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_EAX);
        triton::arch::x86::x86_reg_ax     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_AX);
        triton::arch::x86::x86_reg_ah     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_AH);
        triton::arch::x86::x86_reg_al     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_AL);

        triton::arch::x86::x86_reg_rbx    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ebx    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_EBX);
        triton::arch::x86::x86_reg_bx     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_BX);
        triton::arch::x86::x86_reg_bh     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_BH);
        triton::arch::x86::x86_reg_bl     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_BL);

        triton::arch::x86::x86_reg_rcx    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ecx    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_ECX);
        triton::arch::x86::x86_reg_cx     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CX);
        triton::arch::x86::x86_reg_ch     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CH);
        triton::arch::x86::x86_reg_cl     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CL);

        triton::arch::x86::x86_reg_rdx    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_edx    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_EDX);
        triton::arch::x86::x86_reg_dx     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DX);
        triton::arch::x86::x86_reg_dh     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DH);
        triton::arch::x86::x86_reg_dl     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DL);

        triton::arch::x86::x86_reg_rdi    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_edi    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_EDI);
        triton::arch::x86::x86_reg_di     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DI);
        triton::arch::x86::x86_reg_dil    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DIL);

        triton::arch::x86::x86_reg_rsi    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_esi    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_ESI);
        triton::arch::x86::x86_reg_si     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_SI);
        triton::arch::x86::x86_reg_sil    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_SIL);

        triton::arch::x86::x86_reg_rsp    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_esp    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_ESP);
        triton::arch::x86::x86_reg_sp     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_SP);
        triton::arch::x86::x86_reg_spl    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_SPL);
        triton::arch::x86::x86_reg_stack  = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_ESP);

        triton::arch::x86::x86_reg_rbp    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ebp    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_EBP);
        triton::arch::x86::x86_reg_bp     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_BP);
        triton::arch::x86::x86_reg_bpl    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_BPL);

        triton::arch::x86::x86_reg_rip    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_eip    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_EIP);
        triton::arch::x86::x86_reg_ip     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_IP);
        triton::arch::x86::x86_reg_pc     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_EIP);

        triton::arch::x86::x86_reg_eflags = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_EFLAGS);

        triton::arch::x86::x86_reg_r8     = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r8d    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r8w    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r8b    = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_r9     = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r9d    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r9w    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r9b    = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_r10    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r10d   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r10w   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r10b   = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_r11    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r11d   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r11w   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r11b   = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_r12    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r12d   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r12w   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r12b   = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_r13    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r13d   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r13w   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r13b   = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_r14    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r14d   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r14w   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r14b   = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_r15    = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r15d   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r15w   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_r15b   = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_mm0    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_MM0);
        triton::arch::x86::x86_reg_mm1    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_MM1);
        triton::arch::x86::x86_reg_mm2    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_MM2);
        triton::arch::x86::x86_reg_mm3    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_MM3);
        triton::arch::x86::x86_reg_mm4    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_MM4);
        triton::arch::x86::x86_reg_mm5    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_MM5);
        triton::arch::x86::x86_reg_mm6    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_MM6);
        triton::arch::x86::x86_reg_mm7    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_MM7);

        triton::arch::x86::x86_reg_xmm0   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_XMM0);
        triton::arch::x86::x86_reg_xmm1   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_XMM1);
        triton::arch::x86::x86_reg_xmm2   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_XMM2);
        triton::arch::x86::x86_reg_xmm3   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_XMM3);
        triton::arch::x86::x86_reg_xmm4   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_XMM4);
        triton::arch::x86::x86_reg_xmm5   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_XMM5);
        triton::arch::x86::x86_reg_xmm6   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_XMM6);
        triton::arch::x86::x86_reg_xmm7   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_XMM7);
        triton::arch::x86::x86_reg_xmm8   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_xmm9   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_xmm10  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_xmm11  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_xmm12  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_xmm13  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_xmm14  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_xmm15  = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_ymm0   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_YMM0);
        triton::arch::x86::x86_reg_ymm1   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_YMM1);
        triton::arch::x86::x86_reg_ymm2   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_YMM2);
        triton::arch::x86::x86_reg_ymm3   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_YMM3);
        triton::arch::x86::x86_reg_ymm4   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_YMM4);
        triton::arch::x86::x86_reg_ymm5   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_YMM5);
        triton::arch::x86::x86_reg_ymm6   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_YMM6);
        triton::arch::x86::x86_reg_ymm7   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_YMM7);
        triton::arch::x86::x86_reg_ymm8   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ymm9   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ymm10  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ymm11  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ymm12  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ymm13  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ymm14  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_ymm15  = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_zmm0   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm1   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm2   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm3   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm4   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm5   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm6   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm7   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm8   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm9   = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm10  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm11  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm12  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm13  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm14  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm15  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm16  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm17  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm18  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm19  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm20  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm21  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm22  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm23  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm24  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm25  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm26  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm27  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm28  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm29  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm30  = triton::arch::RegisterOperand();
        triton::arch::x86::x86_reg_zmm31  = triton::arch::RegisterOperand();

        triton::arch::x86::x86_reg_mxcsr  = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_MXCSR);

        triton::arch::x86::x86_reg_cr0    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR0);
        triton::arch::x86::x86_reg_cr1    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR1);
        triton::arch::x86::x86_reg_cr2    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR2);
        triton::arch::x86::x86_reg_cr3    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR3);
        triton::arch::x86::x86_reg_cr4    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR4);
        triton::arch::x86::x86_reg_cr5    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR5);
        triton::arch::x86::x86_reg_cr6    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR6);
        triton::arch::x86::x86_reg_cr7    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR7);
        triton::arch::x86::x86_reg_cr8    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR8);
        triton::arch::x86::x86_reg_cr9    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR9);
        triton::arch::x86::x86_reg_cr10   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR10);
        triton::arch::x86::x86_reg_cr11   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR11);
        triton::arch::x86::x86_reg_cr12   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR12);
        triton::arch::x86::x86_reg_cr13   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR13);
        triton::arch::x86::x86_reg_cr14   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR14);
        triton::arch::x86::x86_reg_cr15   = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CR15);

        triton::arch::x86::x86_reg_ie     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_IE);
        triton::arch::x86::x86_reg_de     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DE);
        triton::arch::x86::x86_reg_ze     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_ZE);
        triton::arch::x86::x86_reg_oe     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_OE);
        triton::arch::x86::x86_reg_ue     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_UE);
        triton::arch::x86::x86_reg_pe     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_PE);
        triton::arch::x86::x86_reg_daz    = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DAZ);
        triton::arch::x86::x86_reg_im     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_IM);
        triton::arch::x86::x86_reg_dm     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DM);
        triton::arch::x86::x86_reg_zm     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_ZM);
        triton::arch::x86::x86_reg_om     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_OM);
        triton::arch::x86::x86_reg_um     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_UM);
        triton::arch::x86::x86_reg_pm     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_PM);
        triton::arch::x86::x86_reg_rl     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_RL);
        triton::arch::x86::x86_reg_rh     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_RH);
        triton::arch::x86::x86_reg_fz     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_FZ);

        triton::arch::x86::x86_reg_af     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_AF);
        triton::arch::x86::x86_reg_cf     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CF);
        triton::arch::x86::x86_reg_df     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DF);
        triton::arch::x86::x86_reg_if     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_IF);
        triton::arch::x86::x86_reg_of     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_OF);
        triton::arch::x86::x86_reg_pf     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_PF);
        triton::arch::x86::x86_reg_sf     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_SF);
        triton::arch::x86::x86_reg_tf     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_TF);
        triton::arch::x86::x86_reg_zf     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_ZF);

        triton::arch::x86::x86_reg_cs     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_CS);
        triton::arch::x86::x86_reg_ds     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_DS);
        triton::arch::x86::x86_reg_es     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_ES);
        triton::arch::x86::x86_reg_fs     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_FS);
        triton::arch::x86::x86_reg_gs     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_GS);
        triton::arch::x86::x86_reg_ss     = triton::arch::RegisterOperand(triton::arch::x86::ID_REG_SS);

        /* Update python env ======================================================== */
        #ifdef TRITON_PYTHON_BINDINGS
          triton::bindings::python::initRegNamespace();
          triton::bindings::python::initCpuSizeNamespace();
          triton::bindings::python::initX86OpcodesNamespace();
          triton::bindings::python::initX86PrefixesNamespace();
          #if defined(__unix__) || defined(__APPLE__)
            triton::bindings::python::initSyscallNamespace();
          #endif
        #endif
      }


      void x86Cpu::clear(void) {
        /* Clear memory */
        this->memory.clear();

        /* Clear registers */
        memset(this->eax,     0x00, sizeof(this->eax));
        memset(this->ebx,     0x00, sizeof(this->ebx));
        memset(this->ecx,     0x00, sizeof(this->ecx));
        memset(this->edx,     0x00, sizeof(this->edx));
        memset(this->edi,     0x00, sizeof(this->edi));
        memset(this->esi,     0x00, sizeof(this->esi));
        memset(this->esp,     0x00, sizeof(this->esp));
        memset(this->ebp,     0x00, sizeof(this->ebp));
        memset(this->eip,     0x00, sizeof(this->eip));
        memset(this->eflags,  0x00, sizeof(this->eflags));
        memset(this->mm0,     0x00, sizeof(this->mm0));
        memset(this->mm1,     0x00, sizeof(this->mm1));
        memset(this->mm2,     0x00, sizeof(this->mm2));
        memset(this->mm3,     0x00, sizeof(this->mm3));
        memset(this->mm4,     0x00, sizeof(this->mm4));
        memset(this->mm5,     0x00, sizeof(this->mm5));
        memset(this->mm6,     0x00, sizeof(this->mm6));
        memset(this->mm7,     0x00, sizeof(this->mm7));
        memset(this->xmm0,    0x00, sizeof(this->xmm0));
        memset(this->xmm1,    0x00, sizeof(this->xmm1));
        memset(this->xmm2,    0x00, sizeof(this->xmm2));
        memset(this->xmm3,    0x00, sizeof(this->xmm3));
        memset(this->xmm4,    0x00, sizeof(this->xmm4));
        memset(this->xmm5,    0x00, sizeof(this->xmm5));
        memset(this->xmm6,    0x00, sizeof(this->xmm6));
        memset(this->xmm7,    0x00, sizeof(this->xmm7));
        memset(this->ymm0,    0x00, sizeof(this->ymm0));
        memset(this->ymm1,    0x00, sizeof(this->ymm1));
        memset(this->ymm2,    0x00, sizeof(this->ymm2));
        memset(this->ymm3,    0x00, sizeof(this->ymm3));
        memset(this->ymm4,    0x00, sizeof(this->ymm4));
        memset(this->ymm5,    0x00, sizeof(this->ymm5));
        memset(this->ymm6,    0x00, sizeof(this->ymm6));
        memset(this->ymm7,    0x00, sizeof(this->ymm7));
        memset(this->mxcsr,   0x00, sizeof(this->mxcsr));
        memset(this->cr0,     0x00, sizeof(this->cr0));
        memset(this->cr1,     0x00, sizeof(this->cr1));
        memset(this->cr2,     0x00, sizeof(this->cr2));
        memset(this->cr3,     0x00, sizeof(this->cr3));
        memset(this->cr4,     0x00, sizeof(this->cr4));
        memset(this->cr5,     0x00, sizeof(this->cr5));
        memset(this->cr6,     0x00, sizeof(this->cr6));
        memset(this->cr7,     0x00, sizeof(this->cr7));
        memset(this->cr8,     0x00, sizeof(this->cr8));
        memset(this->cr9,     0x00, sizeof(this->cr9));
        memset(this->cr10,    0x00, sizeof(this->cr10));
        memset(this->cr11,    0x00, sizeof(this->cr11));
        memset(this->cr12,    0x00, sizeof(this->cr12));
        memset(this->cr13,    0x00, sizeof(this->cr13));
        memset(this->cr14,    0x00, sizeof(this->cr14));
        memset(this->cr15,    0x00, sizeof(this->cr15));
        memset(this->cs,      0x00, sizeof(this->cs));
        memset(this->ds,      0x00, sizeof(this->ds));
        memset(this->es,      0x00, sizeof(this->es));
        memset(this->fs,      0x00, sizeof(this->fs));
        memset(this->gs,      0x00, sizeof(this->gs));
        memset(this->ss,      0x00, sizeof(this->ss));
      }


      void x86Cpu::operator=(const x86Cpu& other) {
        this->copy(other);
      }


      bool x86Cpu::isFlag(triton::uint32 regId) const {
        return ((regId >= triton::arch::x86::ID_REG_AF && regId <= triton::arch::x86::ID_REG_FZ) ? true : false);
      }


      bool x86Cpu::isRegister(triton::uint32 regId) const {
        return (this->isGPR(regId) || this->isMMX(regId) || this->isSSE(regId) || this->isAVX256(regId) || this->isControl(regId) || this->isSegment(regId));
      }


      bool x86Cpu::isRegisterValid(triton::uint32 regId) const {
        return (this->isFlag(regId) || this->isRegister(regId));
      }


      bool x86Cpu::isGPR(triton::uint32 regId) const {
        return ((regId >= triton::arch::x86::ID_REG_EAX && regId <= triton::arch::x86::ID_REG_EFLAGS) ? true : false);
      }


      bool x86Cpu::isMMX(triton::uint32 regId) const {
        return ((regId >= triton::arch::x86::ID_REG_MM0 && regId <= triton::arch::x86::ID_REG_MM7) ? true : false);
      }


      bool x86Cpu::isSSE(triton::uint32 regId) const {
        return ((regId >= triton::arch::x86::ID_REG_MXCSR && regId <= triton::arch::x86::ID_REG_XMM7) ? true : false);
      }


      bool x86Cpu::isAVX256(triton::uint32 regId) const {
        return ((regId >= triton::arch::x86::ID_REG_YMM0 && regId <= triton::arch::x86::ID_REG_YMM7) ? true : false);
      }


      bool x86Cpu::isControl(triton::uint32 regId) const {
        return ((regId >= triton::arch::x86::ID_REG_CR0 && regId <= triton::arch::x86::ID_REG_CR15) ? true : false);
      }


      bool x86Cpu::isSegment(triton::uint32 regId) const {
        return ((regId >= triton::arch::x86::ID_REG_CS && regId <= triton::arch::x86::ID_REG_SS) ? true : false);
      }


      triton::uint32 x86Cpu::invalidRegister(void) const {
        return triton::arch::x86::ID_REG_INVALID;
      }


      triton::uint32 x86Cpu::numberOfRegisters(void) const {
        return triton::arch::x86::ID_REG_LAST_ITEM;
      }


      triton::uint32 x86Cpu::registerSize(void) const {
        return DWORD_SIZE;
      }


      triton::uint32 x86Cpu::registerBitSize(void) const {
        return DWORD_SIZE_BIT;
      }


      std::tuple<std::string, triton::uint32, triton::uint32, triton::uint32> x86Cpu::getRegisterInformation(triton::uint32 reg) const {
        return triton::arch::x86::registerIdToRegisterInformation(reg);
      }


      std::set<triton::arch::RegisterOperand*> x86Cpu::getAllRegisters(void) const {
        std::set<triton::arch::RegisterOperand*> ret;

        for (triton::uint32 index = 0; index < triton::arch::x86::ID_REG_LAST_ITEM; index++) {
          if (this->isRegisterValid(triton::arch::x86::x86_regs[index]->getId()))
            ret.insert(triton::arch::x86::x86_regs[index]);
        }

        return ret;
      }


      std::set<triton::arch::RegisterOperand*> x86Cpu::getParentRegisters(void) const {
        std::set<triton::arch::RegisterOperand*> ret;

        for (triton::uint32 index = 0; index < triton::arch::x86::ID_REG_LAST_ITEM; index++) {
          /* Add GPR */
          if (triton::arch::x86::x86_regs[index]->getSize() == this->registerSize())
            ret.insert(triton::arch::x86::x86_regs[index]);

          /* Add Flags */
          else if (this->isFlag(triton::arch::x86::x86_regs[index]->getId()))
            ret.insert(triton::arch::x86::x86_regs[index]);

          /* Add MMX */
          else if (this->isMMX(triton::arch::x86::x86_regs[index]->getId()))
            ret.insert(triton::arch::x86::x86_regs[index]);

          /* Add SSE */
          else if (this->isSSE(triton::arch::x86::x86_regs[index]->getId()))
            ret.insert(triton::arch::x86::x86_regs[index]);

          /* Add AVX-256 */
          else if (this->isAVX256(triton::arch::x86::x86_regs[index]->getId()))
            ret.insert(triton::arch::x86::x86_regs[index]);

          /* Add Control */
          else if (this->isControl(triton::arch::x86::x86_regs[index]->getId()))
            ret.insert(triton::arch::x86::x86_regs[index]);
        }

        return ret;
      }


      void x86Cpu::disassembly(triton::arch::Instruction& inst) const {
        triton::extlibs::capstone::csh       handle;
        triton::extlibs::capstone::cs_insn*  insn;
        triton::usize                        count = 0;

        /* Check if the opcodes and opcodes' size are defined */
        if (inst.getOpcodes() == nullptr || inst.getSize() == 0)
          throw std::runtime_error("x86Cpu::disassembly(): Opcodes and opcodesSize must be definied.");

        /* Open capstone */
        if (triton::extlibs::capstone::cs_open(triton::extlibs::capstone::CS_ARCH_X86, triton::extlibs::capstone::CS_MODE_32, &handle) != triton::extlibs::capstone::CS_ERR_OK)
          throw std::runtime_error("x86Cpu::disassembly(): Cannot open capstone.");

        /* Init capstone's options */
        triton::extlibs::capstone::cs_option(handle, triton::extlibs::capstone::CS_OPT_DETAIL, triton::extlibs::capstone::CS_OPT_ON);
        triton::extlibs::capstone::cs_option(handle, triton::extlibs::capstone::CS_OPT_SYNTAX, triton::extlibs::capstone::CS_OPT_SYNTAX_INTEL);

        /* Let's disass and build our operands */
        count = triton::extlibs::capstone::cs_disasm(handle, inst.getOpcodes(), inst.getSize(), inst.getAddress(), 0, &insn);
        if (count > 0) {
          triton::extlibs::capstone::cs_detail* detail = insn->detail;
          for (triton::uint32 j = 0; j < 1; j++) {

            /* Init the disassembly */
            std::stringstream str;
            str << insn[j].mnemonic << " " <<  insn[j].op_str;
            inst.setDisassembly(str.str());

            /* Refine the size */
            inst.setSize(insn[j].size);

            /* Init the instruction's type */
            inst.setType(triton::arch::x86::capstoneInstructionToTritonInstruction(insn[j].id));

            /* Init the instruction's prefix */
            inst.setPrefix(triton::arch::x86::capstonePrefixToTritonPrefix(detail->x86.prefix[0]));

            /* Init operands */
            for (triton::uint32 n = 0; n < detail->x86.op_count; n++) {
              triton::extlibs::capstone::cs_x86_op* op = &(detail->x86.operands[n]);
              switch(op->type) {

                case triton::extlibs::capstone::X86_OP_IMM:
                  inst.operands.push_back(triton::arch::OperandWrapper(triton::arch::ImmediateOperand(op->imm, op->size)));
                  break;

                case triton::extlibs::capstone::X86_OP_MEM: {
                  triton::arch::MemoryOperand mem = inst.popMemoryAccess();

                  /* Set the size if the memory is not valid */
                  if (!mem.isValid())
                    mem.setPair(std::make_pair(((op->size * BYTE_SIZE_BIT) - 1), 0));

                  /* LEA if exists */
                  triton::arch::RegisterOperand segment(triton::arch::x86::capstoneRegisterToTritonRegister(op->mem.segment));
                  triton::arch::RegisterOperand base(triton::arch::x86::capstoneRegisterToTritonRegister(op->mem.base));
                  triton::arch::RegisterOperand index(triton::arch::x86::capstoneRegisterToTritonRegister(op->mem.index));
                  triton::arch::ImmediateOperand disp(op->mem.disp, base.isValid() ? base.getSize() : index.isValid() ? index.getSize() : op->size);
                  triton::arch::ImmediateOperand scale(op->mem.scale, base.isValid() ? base.getSize() : index.isValid() ? index.getSize() : op->size);

                  /* Specify that LEA contains a PC relative */
                  if (base.getId() == TRITON_X86_REG_PC.getId())
                    mem.setPcRelative(inst.getNextAddress());

                  mem.setSegmentRegister(segment);
                  mem.setBaseRegister(base);
                  mem.setIndexRegister(index);
                  mem.setDisplacement(disp);
                  mem.setScale(scale);

                  inst.operands.push_back(triton::arch::OperandWrapper(mem));
                  break;
                }

                case triton::extlibs::capstone::X86_OP_REG:
                  inst.operands.push_back(triton::arch::OperandWrapper(inst.getRegisterState(triton::arch::x86::capstoneRegisterToTritonRegister(op->reg))));
                  break;

                default:
                  break;
              }
            }

          }
          /* Set branch */
          if (detail->groups_count > 0) {
            for (triton::uint32 n = 0; n < detail->groups_count; n++) {
              if (detail->groups[n] == triton::extlibs::capstone::X86_GRP_JUMP)
                inst.setBranch(true);
              if (detail->groups[n] == triton::extlibs::capstone::X86_GRP_JUMP ||
                  detail->groups[n] == triton::extlibs::capstone::X86_GRP_CALL ||
                  detail->groups[n] == triton::extlibs::capstone::X86_GRP_RET)
                inst.setControlFlow(true);
            }
          }
          triton::extlibs::capstone::cs_free(insn, count);
        }
        else
          throw std::runtime_error("x86Cpu::disassembly(): Failed to disassemble the given code.");

        triton::extlibs::capstone::cs_close(&handle);
        return;
      }


      void x86Cpu::buildSemantics(triton::arch::Instruction& inst) const {
        if (!inst.getType())
          throw std::runtime_error("x86Cpu::buildSemantics(): You must disassemble the instruction before.");
        triton::arch::x86::semantics::build(inst);
      }


      triton::uint8 x86Cpu::getLastMemoryValue(triton::uint64 addr) const {
        if (this->memory.find(addr) == this->memory.end())
          return 0x00;
        return this->memory.at(addr);
      }


      triton::uint512 x86Cpu::getLastMemoryValue(const triton::arch::MemoryOperand& mem) const {
        triton::uint512 ret = 0;
        triton::uint64 addr = mem.getAddress();
        triton::uint32 size = mem.getSize();

        if (size == 0 || size > DQQWORD_SIZE)
          throw std::invalid_argument("x86Cpu::getLastMemoryValue(): Invalid size memory.");

        for (triton::sint32 i = size-1; i >= 0; i--)
          ret = ((ret << BYTE_SIZE_BIT) | this->getLastMemoryValue(addr+i));

        return ret;
      }


      std::vector<triton::uint8> x86Cpu::getLastMemoryAreaValue(triton::uint64 baseAddr, triton::usize size) const {
        std::vector<triton::uint8> area;

        for (triton::usize index = 0; index < size; index++)
          area.push_back(this->getLastMemoryValue(baseAddr+index));

        return area;
      }


      triton::uint512 x86Cpu::getLastRegisterValue(const triton::arch::RegisterOperand& reg) const {
        triton::uint512 value = 0;
        switch (reg.getId()) {
          case triton::arch::x86::ID_REG_EAX: return (*((triton::uint32*)(this->eax)));
          case triton::arch::x86::ID_REG_AX:  return (*((triton::uint16*)(this->eax)));
          case triton::arch::x86::ID_REG_AH:  return (*((triton::uint8*)(this->eax+1)));
          case triton::arch::x86::ID_REG_AL:  return (*((triton::uint8*)(this->eax)));

          case triton::arch::x86::ID_REG_EBX: return (*((triton::uint32*)(this->ebx)));
          case triton::arch::x86::ID_REG_BX:  return (*((triton::uint16*)(this->ebx)));
          case triton::arch::x86::ID_REG_BH:  return (*((triton::uint8*)(this->ebx+1)));
          case triton::arch::x86::ID_REG_BL:  return (*((triton::uint8*)(this->ebx)));

          case triton::arch::x86::ID_REG_ECX: return (*((triton::uint32*)(this->ecx)));
          case triton::arch::x86::ID_REG_CX:  return (*((triton::uint16*)(this->ecx)));
          case triton::arch::x86::ID_REG_CH:  return (*((triton::uint8*)(this->ecx+1)));
          case triton::arch::x86::ID_REG_CL:  return (*((triton::uint8*)(this->ecx)));

          case triton::arch::x86::ID_REG_EDX: return (*((triton::uint32*)(this->edx)));
          case triton::arch::x86::ID_REG_DX:  return (*((triton::uint16*)(this->edx)));
          case triton::arch::x86::ID_REG_DH:  return (*((triton::uint8*)(this->edx+1)));
          case triton::arch::x86::ID_REG_DL:  return (*((triton::uint8*)(this->edx)));

          case triton::arch::x86::ID_REG_EDI: return (*((triton::uint32*)(this->edi)));
          case triton::arch::x86::ID_REG_DI:  return (*((triton::uint16*)(this->edi)));
          case triton::arch::x86::ID_REG_DIL: return (*((triton::uint8*)(this->edi)));

          case triton::arch::x86::ID_REG_ESI: return (*((triton::uint32*)(this->esi)));
          case triton::arch::x86::ID_REG_SI:  return (*((triton::uint16*)(this->esi)));
          case triton::arch::x86::ID_REG_SIL: return (*((triton::uint8*)(this->esi)));

          case triton::arch::x86::ID_REG_ESP: return (*((triton::uint32*)(this->esp)));
          case triton::arch::x86::ID_REG_SP:  return (*((triton::uint16*)(this->esp)));
          case triton::arch::x86::ID_REG_SPL: return (*((triton::uint8*)(this->esp)));

          case triton::arch::x86::ID_REG_EBP: return (*((triton::uint32*)(this->ebp)));
          case triton::arch::x86::ID_REG_BP:  return (*((triton::uint16*)(this->ebp)));
          case triton::arch::x86::ID_REG_BPL: return (*((triton::uint8*)(this->ebp)));

          case triton::arch::x86::ID_REG_EIP: return (*((triton::uint32*)(this->eip)));
          case triton::arch::x86::ID_REG_IP:  return (*((triton::uint16*)(this->eip)));

          case triton::arch::x86::ID_REG_EFLAGS: return (*((triton::uint32*)(this->eflags)));

          case triton::arch::x86::ID_REG_MM0:  return (*((triton::uint64*)(this->mm0)));
          case triton::arch::x86::ID_REG_MM1:  return (*((triton::uint64*)(this->mm1)));
          case triton::arch::x86::ID_REG_MM2:  return (*((triton::uint64*)(this->mm2)));
          case triton::arch::x86::ID_REG_MM3:  return (*((triton::uint64*)(this->mm3)));
          case triton::arch::x86::ID_REG_MM4:  return (*((triton::uint64*)(this->mm4)));
          case triton::arch::x86::ID_REG_MM5:  return (*((triton::uint64*)(this->mm5)));
          case triton::arch::x86::ID_REG_MM6:  return (*((triton::uint64*)(this->mm6)));
          case triton::arch::x86::ID_REG_MM7:  return (*((triton::uint64*)(this->mm7)));

          case triton::arch::x86::ID_REG_XMM0: value = triton::utils::fromBufferToUint<triton::uint128>(this->xmm0); return value;
          case triton::arch::x86::ID_REG_XMM1: value = triton::utils::fromBufferToUint<triton::uint128>(this->xmm1); return value;
          case triton::arch::x86::ID_REG_XMM2: value = triton::utils::fromBufferToUint<triton::uint128>(this->xmm2); return value;
          case triton::arch::x86::ID_REG_XMM3: value = triton::utils::fromBufferToUint<triton::uint128>(this->xmm3); return value;
          case triton::arch::x86::ID_REG_XMM4: value = triton::utils::fromBufferToUint<triton::uint128>(this->xmm4); return value;
          case triton::arch::x86::ID_REG_XMM5: value = triton::utils::fromBufferToUint<triton::uint128>(this->xmm5); return value;
          case triton::arch::x86::ID_REG_XMM6: value = triton::utils::fromBufferToUint<triton::uint128>(this->xmm6); return value;
          case triton::arch::x86::ID_REG_XMM7: value = triton::utils::fromBufferToUint<triton::uint128>(this->xmm7); return value;

          case triton::arch::x86::ID_REG_YMM0: value = triton::utils::fromBufferToUint<triton::uint256>(this->ymm0); return value;
          case triton::arch::x86::ID_REG_YMM1: value = triton::utils::fromBufferToUint<triton::uint256>(this->ymm1); return value;
          case triton::arch::x86::ID_REG_YMM2: value = triton::utils::fromBufferToUint<triton::uint256>(this->ymm2); return value;
          case triton::arch::x86::ID_REG_YMM3: value = triton::utils::fromBufferToUint<triton::uint256>(this->ymm3); return value;
          case triton::arch::x86::ID_REG_YMM4: value = triton::utils::fromBufferToUint<triton::uint256>(this->ymm4); return value;
          case triton::arch::x86::ID_REG_YMM5: value = triton::utils::fromBufferToUint<triton::uint256>(this->ymm5); return value;
          case triton::arch::x86::ID_REG_YMM6: value = triton::utils::fromBufferToUint<triton::uint256>(this->ymm6); return value;
          case triton::arch::x86::ID_REG_YMM7: value = triton::utils::fromBufferToUint<triton::uint256>(this->ymm7); return value;

          case triton::arch::x86::ID_REG_MXCSR: return (*((triton::uint32*)(this->mxcsr)));

          case triton::arch::x86::ID_REG_CR0:  return (*((triton::uint32*)(this->cr0)));
          case triton::arch::x86::ID_REG_CR1:  return (*((triton::uint32*)(this->cr1)));
          case triton::arch::x86::ID_REG_CR2:  return (*((triton::uint32*)(this->cr2)));
          case triton::arch::x86::ID_REG_CR3:  return (*((triton::uint32*)(this->cr3)));
          case triton::arch::x86::ID_REG_CR4:  return (*((triton::uint32*)(this->cr4)));
          case triton::arch::x86::ID_REG_CR5:  return (*((triton::uint32*)(this->cr5)));
          case triton::arch::x86::ID_REG_CR6:  return (*((triton::uint32*)(this->cr6)));
          case triton::arch::x86::ID_REG_CR7:  return (*((triton::uint32*)(this->cr7)));
          case triton::arch::x86::ID_REG_CR8:  return (*((triton::uint32*)(this->cr8)));
          case triton::arch::x86::ID_REG_CR9:  return (*((triton::uint32*)(this->cr9)));
          case triton::arch::x86::ID_REG_CR10: return (*((triton::uint32*)(this->cr10)));
          case triton::arch::x86::ID_REG_CR11: return (*((triton::uint32*)(this->cr11)));
          case triton::arch::x86::ID_REG_CR12: return (*((triton::uint32*)(this->cr12)));
          case triton::arch::x86::ID_REG_CR13: return (*((triton::uint32*)(this->cr13)));
          case triton::arch::x86::ID_REG_CR14: return (*((triton::uint32*)(this->cr14)));
          case triton::arch::x86::ID_REG_CR15: return (*((triton::uint32*)(this->cr15)));

          case triton::arch::x86::ID_REG_IE:  return (((*((triton::uint32*)(this->mxcsr))) >> 0) & 1);
          case triton::arch::x86::ID_REG_DE:  return (((*((triton::uint32*)(this->mxcsr))) >> 1) & 1);
          case triton::arch::x86::ID_REG_ZE:  return (((*((triton::uint32*)(this->mxcsr))) >> 2) & 1);
          case triton::arch::x86::ID_REG_OE:  return (((*((triton::uint32*)(this->mxcsr))) >> 3) & 1);
          case triton::arch::x86::ID_REG_UE:  return (((*((triton::uint32*)(this->mxcsr))) >> 4) & 1);
          case triton::arch::x86::ID_REG_PE:  return (((*((triton::uint32*)(this->mxcsr))) >> 5) & 1);
          case triton::arch::x86::ID_REG_DAZ: return (((*((triton::uint32*)(this->mxcsr))) >> 6) & 1);
          case triton::arch::x86::ID_REG_IM:  return (((*((triton::uint32*)(this->mxcsr))) >> 7) & 1);
          case triton::arch::x86::ID_REG_DM:  return (((*((triton::uint32*)(this->mxcsr))) >> 8) & 1);
          case triton::arch::x86::ID_REG_ZM:  return (((*((triton::uint32*)(this->mxcsr))) >> 9) & 1);
          case triton::arch::x86::ID_REG_OM:  return (((*((triton::uint32*)(this->mxcsr))) >> 10) & 1);
          case triton::arch::x86::ID_REG_UM:  return (((*((triton::uint32*)(this->mxcsr))) >> 11) & 1);
          case triton::arch::x86::ID_REG_PM:  return (((*((triton::uint32*)(this->mxcsr))) >> 12) & 1);
          case triton::arch::x86::ID_REG_RL:  return (((*((triton::uint32*)(this->mxcsr))) >> 13) & 1);
          case triton::arch::x86::ID_REG_RH:  return (((*((triton::uint32*)(this->mxcsr))) >> 14) & 1);
          case triton::arch::x86::ID_REG_FZ:  return (((*((triton::uint32*)(this->mxcsr))) >> 15) & 1);

          case triton::arch::x86::ID_REG_CF: return (((*((triton::uint32*)(this->eflags))) >> 0) & 1);
          case triton::arch::x86::ID_REG_PF: return (((*((triton::uint32*)(this->eflags))) >> 2) & 1);
          case triton::arch::x86::ID_REG_AF: return (((*((triton::uint32*)(this->eflags))) >> 4) & 1);
          case triton::arch::x86::ID_REG_ZF: return (((*((triton::uint32*)(this->eflags))) >> 6) & 1);
          case triton::arch::x86::ID_REG_SF: return (((*((triton::uint32*)(this->eflags))) >> 7) & 1);
          case triton::arch::x86::ID_REG_TF: return (((*((triton::uint32*)(this->eflags))) >> 8) & 1);
          case triton::arch::x86::ID_REG_IF: return (((*((triton::uint32*)(this->eflags))) >> 9) & 1);
          case triton::arch::x86::ID_REG_DF: return (((*((triton::uint32*)(this->eflags))) >> 10) & 1);
          case triton::arch::x86::ID_REG_OF: return (((*((triton::uint32*)(this->eflags))) >> 11) & 1);

          case triton::arch::x86::ID_REG_CS: return (*((triton::uint32*)(this->cs)));
          case triton::arch::x86::ID_REG_DS: return (*((triton::uint32*)(this->ds)));
          case triton::arch::x86::ID_REG_ES: return (*((triton::uint32*)(this->es)));
          case triton::arch::x86::ID_REG_FS: return (*((triton::uint32*)(this->fs)));
          case triton::arch::x86::ID_REG_GS: return (*((triton::uint32*)(this->gs)));
          case triton::arch::x86::ID_REG_SS: return (*((triton::uint32*)(this->ss)));

          default:
            throw std::invalid_argument("x86Cpu::getLastRegisterValue(): Invalid register.");
        }

        return value;
      }


      void x86Cpu::setLastMemoryValue(triton::uint64 addr, triton::uint8 value) {
        this->memory[addr] = value;
      }


      void x86Cpu::setLastMemoryValue(const triton::arch::MemoryOperand& mem) {
        triton::uint64 addr = mem.getAddress();
        triton::uint32 size = mem.getSize();
        triton::uint512 cv  = mem.getConcreteValue();

        if (size == 0 || size > DQQWORD_SIZE)
          throw std::invalid_argument("x86Cpu::setLastMemoryValue(): Invalid size memory.");

        for (triton::uint32 i = 0; i < size; i++) {
          this->memory[addr+i] = (cv & 0xff).convert_to<triton::uint8>();
          cv >>= 8;
        }
      }


      void x86Cpu::setLastMemoryAreaValue(triton::uint64 baseAddr, const std::vector<triton::uint8>& values) {
        for (triton::usize index = 0; index < values.size(); index++) {
          this->memory[baseAddr+index] = values[index];
        }
      }


      void x86Cpu::setLastMemoryAreaValue(triton::uint64 baseAddr, const triton::uint8* area, triton::usize size) {
        for (triton::usize index = 0; index < size; index++) {
          this->memory[baseAddr+index] = area[index];
        }
      }


      void x86Cpu::setLastRegisterValue(const triton::arch::RegisterOperand& reg) {
        triton::uint512 value = reg.getConcreteValue();

        switch (reg.getId()) {
          case triton::arch::x86::ID_REG_EAX: (*((triton::uint32*)(this->eax)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_AX:  (*((triton::uint16*)(this->eax)))  = value.convert_to<triton::uint16>(); break;
          case triton::arch::x86::ID_REG_AH:  (*((triton::uint8*)(this->eax+1))) = value.convert_to<triton::uint8>(); break;
          case triton::arch::x86::ID_REG_AL:  (*((triton::uint8*)(this->eax)))   = value.convert_to<triton::uint8>(); break;

          case triton::arch::x86::ID_REG_EBX: (*((triton::uint32*)(this->ebx)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_BX:  (*((triton::uint16*)(this->ebx)))  = value.convert_to<triton::uint16>(); break;
          case triton::arch::x86::ID_REG_BH:  (*((triton::uint8*)(this->ebx+1))) = value.convert_to<triton::uint8>(); break;
          case triton::arch::x86::ID_REG_BL:  (*((triton::uint8*)(this->ebx)))   = value.convert_to<triton::uint8>(); break;

          case triton::arch::x86::ID_REG_ECX: (*((triton::uint32*)(this->ecx)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CX:  (*((triton::uint16*)(this->ecx)))  = value.convert_to<triton::uint16>(); break;
          case triton::arch::x86::ID_REG_CH:  (*((triton::uint8*)(this->ecx+1))) = value.convert_to<triton::uint8>(); break;
          case triton::arch::x86::ID_REG_CL:  (*((triton::uint8*)(this->ecx)))   = value.convert_to<triton::uint8>(); break;

          case triton::arch::x86::ID_REG_EDX: (*((triton::uint32*)(this->edx)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_DX:  (*((triton::uint16*)(this->edx)))  = value.convert_to<triton::uint16>(); break;
          case triton::arch::x86::ID_REG_DH:  (*((triton::uint8*)(this->edx+1))) = value.convert_to<triton::uint8>(); break;
          case triton::arch::x86::ID_REG_DL:  (*((triton::uint8*)(this->edx)))   = value.convert_to<triton::uint8>(); break;

          case triton::arch::x86::ID_REG_EDI: (*((triton::uint32*)(this->edi)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_DI:  (*((triton::uint16*)(this->edi)))  = value.convert_to<triton::uint16>(); break;
          case triton::arch::x86::ID_REG_DIL: (*((triton::uint8*)(this->edi)))   = value.convert_to<triton::uint8>(); break;

          case triton::arch::x86::ID_REG_ESI: (*((triton::uint32*)(this->esi)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_SI:  (*((triton::uint16*)(this->esi)))  = value.convert_to<triton::uint16>(); break;
          case triton::arch::x86::ID_REG_SIL: (*((triton::uint8*)(this->esi)))   = value.convert_to<triton::uint8>(); break;

          case triton::arch::x86::ID_REG_ESP: (*((triton::uint32*)(this->esp)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_SP:  (*((triton::uint16*)(this->esp)))  = value.convert_to<triton::uint16>(); break;
          case triton::arch::x86::ID_REG_SPL: (*((triton::uint8*)(this->esp)))   = value.convert_to<triton::uint8>(); break;

          case triton::arch::x86::ID_REG_EBP: (*((triton::uint32*)(this->ebp)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_BP:  (*((triton::uint16*)(this->ebp)))  = value.convert_to<triton::uint16>(); break;
          case triton::arch::x86::ID_REG_BPL: (*((triton::uint8*)(this->ebp)))   = value.convert_to<triton::uint8>(); break;

          case triton::arch::x86::ID_REG_EIP: (*((triton::uint32*)(this->eip)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_IP:  (*((triton::uint16*)(this->eip)))  = value.convert_to<triton::uint16>(); break;

          case triton::arch::x86::ID_REG_EFLAGS: (*((triton::uint32*)(this->eflags))) = value.convert_to<triton::uint32>(); break;

          case triton::arch::x86::ID_REG_CF: {
            triton::uint32 b = (*((triton::uint32*)(this->eflags)));
            (*((triton::uint32*)(this->eflags))) = value.convert_to<bool>() ? b | (1 << 0) : b & ~(1 << 0);
            break;
          }
          case triton::arch::x86::ID_REG_PF: {
            triton::uint32 b = (*((triton::uint32*)(this->eflags)));
            (*((triton::uint32*)(this->eflags))) = value.convert_to<bool>() ? b | (1 << 2) : b & ~(1 << 2);
            break;
          }
          case triton::arch::x86::ID_REG_AF: {
            triton::uint32 b = (*((triton::uint32*)(this->eflags)));
            (*((triton::uint32*)(this->eflags))) = value.convert_to<bool>() ? b | (1 << 4) : b & ~(1 << 4);
            break;
          }
          case triton::arch::x86::ID_REG_ZF: {
            triton::uint32 b = (*((triton::uint32*)(this->eflags)));
            (*((triton::uint32*)(this->eflags))) = value.convert_to<bool>() ? b | (1 << 6) : b & ~(1 << 6);
            break;
          }
          case triton::arch::x86::ID_REG_SF: {
            triton::uint32 b = (*((triton::uint32*)(this->eflags)));
            (*((triton::uint32*)(this->eflags))) = value.convert_to<bool>() ? b | (1 << 7) : b & ~(1 << 7);
            break;
          }
          case triton::arch::x86::ID_REG_TF: {
            triton::uint32 b = (*((triton::uint32*)(this->eflags)));
            (*((triton::uint32*)(this->eflags))) = value.convert_to<bool>() ? b | (1 << 8) : b & ~(1 << 8);
            break;
          }
          case triton::arch::x86::ID_REG_IF: {
            triton::uint32 b = (*((triton::uint32*)(this->eflags)));
            (*((triton::uint32*)(this->eflags))) = value.convert_to<bool>() ? b | (1 << 9) : b & ~(1 << 9);
            break;
          }
          case triton::arch::x86::ID_REG_DF: {
            triton::uint32 b = (*((triton::uint32*)(this->eflags)));
            (*((triton::uint32*)(this->eflags))) = value.convert_to<bool>() ? b | (1 << 10) : b & ~(1 << 10);
            break;
          }
          case triton::arch::x86::ID_REG_OF: {
            triton::uint32 b = (*((triton::uint32*)(this->eflags)));
            (*((triton::uint32*)(this->eflags))) = value.convert_to<bool>() ? b | (1 << 11) : b & ~(1 << 11);
            break;
          }

          case triton::arch::x86::ID_REG_MM0:  (*((triton::uint64*)(this->mm0))) = value.convert_to<triton::uint64>(); break;
          case triton::arch::x86::ID_REG_MM1:  (*((triton::uint64*)(this->mm1))) = value.convert_to<triton::uint64>(); break;
          case triton::arch::x86::ID_REG_MM2:  (*((triton::uint64*)(this->mm2))) = value.convert_to<triton::uint64>(); break;
          case triton::arch::x86::ID_REG_MM3:  (*((triton::uint64*)(this->mm3))) = value.convert_to<triton::uint64>(); break;
          case triton::arch::x86::ID_REG_MM4:  (*((triton::uint64*)(this->mm4))) = value.convert_to<triton::uint64>(); break;
          case triton::arch::x86::ID_REG_MM5:  (*((triton::uint64*)(this->mm5))) = value.convert_to<triton::uint64>(); break;
          case triton::arch::x86::ID_REG_MM6:  (*((triton::uint64*)(this->mm6))) = value.convert_to<triton::uint64>(); break;
          case triton::arch::x86::ID_REG_MM7:  (*((triton::uint64*)(this->mm7))) = value.convert_to<triton::uint64>(); break;

          case triton::arch::x86::ID_REG_XMM0: triton::utils::fromUintToBuffer(value.convert_to<triton::uint128>(), this->xmm0); break;
          case triton::arch::x86::ID_REG_XMM1: triton::utils::fromUintToBuffer(value.convert_to<triton::uint128>(), this->xmm1); break;
          case triton::arch::x86::ID_REG_XMM2: triton::utils::fromUintToBuffer(value.convert_to<triton::uint128>(), this->xmm2); break;
          case triton::arch::x86::ID_REG_XMM3: triton::utils::fromUintToBuffer(value.convert_to<triton::uint128>(), this->xmm3); break;
          case triton::arch::x86::ID_REG_XMM4: triton::utils::fromUintToBuffer(value.convert_to<triton::uint128>(), this->xmm4); break;
          case triton::arch::x86::ID_REG_XMM5: triton::utils::fromUintToBuffer(value.convert_to<triton::uint128>(), this->xmm5); break;
          case triton::arch::x86::ID_REG_XMM6: triton::utils::fromUintToBuffer(value.convert_to<triton::uint128>(), this->xmm6); break;
          case triton::arch::x86::ID_REG_XMM7: triton::utils::fromUintToBuffer(value.convert_to<triton::uint128>(), this->xmm7); break;

          case triton::arch::x86::ID_REG_YMM0: triton::utils::fromUintToBuffer(value.convert_to<triton::uint256>(), this->ymm0); break;
          case triton::arch::x86::ID_REG_YMM1: triton::utils::fromUintToBuffer(value.convert_to<triton::uint256>(), this->ymm1); break;
          case triton::arch::x86::ID_REG_YMM2: triton::utils::fromUintToBuffer(value.convert_to<triton::uint256>(), this->ymm2); break;
          case triton::arch::x86::ID_REG_YMM3: triton::utils::fromUintToBuffer(value.convert_to<triton::uint256>(), this->ymm3); break;
          case triton::arch::x86::ID_REG_YMM4: triton::utils::fromUintToBuffer(value.convert_to<triton::uint256>(), this->ymm4); break;
          case triton::arch::x86::ID_REG_YMM5: triton::utils::fromUintToBuffer(value.convert_to<triton::uint256>(), this->ymm5); break;
          case triton::arch::x86::ID_REG_YMM6: triton::utils::fromUintToBuffer(value.convert_to<triton::uint256>(), this->ymm6); break;
          case triton::arch::x86::ID_REG_YMM7: triton::utils::fromUintToBuffer(value.convert_to<triton::uint256>(), this->ymm7); break;

          case triton::arch::x86::ID_REG_MXCSR: (*((triton::uint32*)(this->mxcsr))) = value.convert_to<triton::uint32>(); break;

          case triton::arch::x86::ID_REG_IE: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 0) : b & ~(1 << 0);
            break;
          }
          case triton::arch::x86::ID_REG_DE: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 1) : b & ~(1 << 1);
            break;
          }
          case triton::arch::x86::ID_REG_ZE: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 2) : b & ~(1 << 2);
            break;
          }
          case triton::arch::x86::ID_REG_OE: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 3) : b & ~(1 << 3);
            break;
          }
          case triton::arch::x86::ID_REG_UE: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 4) : b & ~(1 << 4);
            break;
          }
          case triton::arch::x86::ID_REG_PE: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 5) : b & ~(1 << 5);
            break;
          }
          case triton::arch::x86::ID_REG_DAZ: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 6) : b & ~(1 << 6);
            break;
          }
          case triton::arch::x86::ID_REG_IM: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 7) : b & ~(1 << 7);
            break;
          }
          case triton::arch::x86::ID_REG_DM: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 8) : b & ~(1 << 8);
            break;
          }
          case triton::arch::x86::ID_REG_ZM: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 9) : b & ~(1 << 9);
            break;
          }
          case triton::arch::x86::ID_REG_OM: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 10) : b & ~(1 << 10);
            break;
          }
          case triton::arch::x86::ID_REG_UM: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 11) : b & ~(1 << 11);
            break;
          }
          case triton::arch::x86::ID_REG_PM: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 12) : b & ~(1 << 12);
            break;
          }
          case triton::arch::x86::ID_REG_RL: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 13) : b & ~(1 << 13);
            break;
          }
          case triton::arch::x86::ID_REG_RH: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 14) : b & ~(1 << 14);
            break;
          }
          case triton::arch::x86::ID_REG_FZ: {
            triton::uint32 b = (*((triton::uint32*)(this->mxcsr)));
            (*((triton::uint32*)(this->mxcsr))) = value.convert_to<bool>() ? b | (1 << 15) : b & ~(1 << 15);
            break;
          }

          case triton::arch::x86::ID_REG_CR0:  (*((triton::uint32*)(this->cr0)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR1:  (*((triton::uint32*)(this->cr1)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR2:  (*((triton::uint32*)(this->cr2)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR3:  (*((triton::uint32*)(this->cr3)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR4:  (*((triton::uint32*)(this->cr4)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR5:  (*((triton::uint32*)(this->cr5)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR6:  (*((triton::uint32*)(this->cr6)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR7:  (*((triton::uint32*)(this->cr7)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR8:  (*((triton::uint32*)(this->cr8)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR9:  (*((triton::uint32*)(this->cr9)))  = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR10: (*((triton::uint32*)(this->cr10))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR11: (*((triton::uint32*)(this->cr11))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR12: (*((triton::uint32*)(this->cr12))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR13: (*((triton::uint32*)(this->cr13))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR14: (*((triton::uint32*)(this->cr14))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_CR15: (*((triton::uint32*)(this->cr15))) = value.convert_to<triton::uint32>(); break;

          case triton::arch::x86::ID_REG_CS:  (*((triton::uint32*)(this->cs))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_DS:  (*((triton::uint32*)(this->ds))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_ES:  (*((triton::uint32*)(this->es))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_FS:  (*((triton::uint32*)(this->fs))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_GS:  (*((triton::uint32*)(this->gs))) = value.convert_to<triton::uint32>(); break;
          case triton::arch::x86::ID_REG_SS:  (*((triton::uint32*)(this->ss))) = value.convert_to<triton::uint32>(); break;

          default:
            throw std::invalid_argument("x86Cpu:setLastRegisterValue() - Invalid register.");
        }
      }

    }; /* x86 namespace */
  }; /* arch namespace */
}; /* triton namespace */


/**
 * @brief		EndoQuest Robotics JARVIS EtherCAT slave object header
 * @details		
 * @author		inode(joongyoung.eom@endoquestrobotics.com), sean(sean.lee@endoquestrobotics.com)
 * @version		initial
 * @copyright	ENDOQUEST, Inc. All rights reserved.
 */

#ifndef __SSI_JARVIS_OBJ_H__
#define __SSI_JARVIS_OBJ_H__

#include <cstdint>
#include <cstddef>

#include <ssi/coobj.h>

#if !defined(__ORDER_LITTLE_ENDIAN__)
# error "cannot support the reverse bitfield order"
#endif

namespace ssi
{
	namespace node
	{
		class jarvis_obj
		{
		public:
			class ControlParam : public coobj<uint32_t>
			{
			public:
				ControlParam() : coobj<uint32_t>(0x0005, 0x01u, rdonly, yes) { }
				virtual ~ControlParam() { }
				union data {
					struct __attribute__((packed)) pack_t {
						value_type stb_dir : 2;
						value_type : 2;
						value_type emg : 1;
						value_type : 2;
						value_type rcy : 1;
						value_type rmt_dir : 2;
						value_type rmt_act : 1;
						value_type : 1;
						value_type max_spd : 16;
					} pack;
					value_type value;
				};
			};

			class DrivingOffset : public coobj<uint32_t>
			{
			public:
				DrivingOffset() : coobj<uint32_t>(0x0005, 0x02u, rdonly, yes) { }
				virtual ~DrivingOffset() { }
			};

			class SteeringOffset : public coobj<uint32_t>
			{
			public:
				SteeringOffset() : coobj<uint32_t>(0x0005, 0x03u, rdonly, yes) { }
				virtual ~SteeringOffset() { }
			};

			class StatusControlParam : public coobj<uint32_t>
			{
			public:
				StatusControlParam() : coobj<uint32_t>(0x0005, 0x04u, rdonly, yes) { }
				virtual ~StatusControlParam() { }

				union data {
					struct __attribute__ ((packed)) pack_t {
						value_type parm5 : 2;
						value_type parm4 : 2;
						value_type parm3 : 2;
						value_type parm2 : 2;
						value_type parm1 : 2;
					} pack;
					value_type value;
				};
				static constexpr value_type parm_positive = 0x1;
				static constexpr value_type parm_negative = 0x2;
			};

			class ParmPosition1 : public coobj<uint32_t>
			{
			public:
				ParmPosition1() : coobj<uint32_t>(0x0005, 0x01u, wronly, yes) { }
				~ParmPosition1() { }
			};

			class ParmPosition2 : public coobj<uint32_t>
			{
			public:
				ParmPosition2() : coobj<uint32_t>(0x0005, 0x02u, wronly, yes) { }
				~ParmPosition2() { }
			};

			class ParmPosition3 : public coobj<uint32_t>
			{
			public:
				ParmPosition3() : coobj<uint32_t>(0x0005, 0x03u, wronly, yes) { }
				~ParmPosition3() { }
			};

			class ParmPosition4 : public coobj<uint32_t>
			{
			public:
				ParmPosition4() : coobj<uint32_t>(0x0005, 0x04u, wronly, yes) { }
				~ParmPosition4() { }
			};

			class ParmPosition5 : public coobj<uint32_t>
			{
			public:
				ParmPosition5() : coobj<uint32_t>(0x0005, 0x05u, wronly, yes) { }
				~ParmPosition5() { }
			};

			class DrivingLoadcellValue : public coobj<uint32_t>
			{
			public:
				DrivingLoadcellValue() : coobj<uint32_t>(0x0005, 0x06u, wronly, yes) { }
				~DrivingLoadcellValue() { }
			};

			class SteeringLoadcellValue : public coobj<uint32_t>
			{
			public:
				SteeringLoadcellValue() : coobj<uint32_t>(0x0005, 0x07u, wronly, yes) { }
				~SteeringLoadcellValue() { }
			};

			class DrivingLoadcellScaled : public coobj<uint32_t>
			{
			public:
				DrivingLoadcellScaled() : coobj<uint32_t>(0x0005, 0x08u, wronly, yes) { }
				~DrivingLoadcellScaled() { }
			};

			class SteeringLoadcellScaled : public coobj<uint32_t>
			{
			public:
				SteeringLoadcellScaled() : coobj<uint32_t>(0x0005, 0x09u, wronly, yes) { }
				~SteeringLoadcellScaled() { }
			};

			class SubSystemStatus : public coobj<uint32_t>
			{
			public:
				SubSystemStatus() : coobj<uint32_t>(0x0005, 0x0au, wronly, yes) { }
				~SubSystemStatus() { }
				union data {
					struct __attribute__ ((packed)) pack_t {
						value_type : 7;
						value_type pwr_con : 1;
						value_type : 3; 
						value_type rmt_sts : 1;
						value_type emg_sts : 1;
						value_type : 3;
						value_type bat_lvl : 8; 
						value_type : 8; 
					} pack;
					value_type value;
				};
			};

			class DrivingSystemStatus : public coobj<uint32_t>
			{
			public:
				DrivingSystemStatus() : coobj<uint32_t>(0x0005, 0xbu, wronly, yes) { }
				~DrivingSystemStatus() { }
				union data {
					struct __attribute__ ((packed)) pack_t {
						value_type : 2;
						value_type dri_act : 2;
						value_type : 2;
						value_type dir_dir : 2;
						value_type : 4;
						value_type stb_sts : 4;
						value_type dri_csp : 16;
					} pack;
					value_type value;
				};
			};
		};
	}
}

#endif // __SSI_JARVIS_OBJ_H__

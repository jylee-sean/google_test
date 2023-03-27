/**
 * @brief		EndoQuest Robotics JARVIS EtherCAT slave class
 * @details		
 * @author		inode(joongyoung.eom@endoquestrobotics.com), sean(sean.lee@endoquestrobotics.com)
 * @version		experimental
 * @copyright	EndoQuest Robotics, Inc. All rights reserved.
 */

#ifndef __SSI_NODE_JARVIS_H__
#define __SSI_NODE_JARVIS_H__

#include <bitset>

#include <ssi/coobj.h>
#include <ssi/node/base.h>
#include <ssi/node/jarvis_obj.h>

namespace ssi
{
	namespace node
	{
		/**
		 * EndoQuest Robotics JARVIS slave class
		 */
		class jarvis : public ssi::node::base
		{
		public:
			struct input_t {
				copdo<jarvis_obj::ControlParam::value_type> controlParam;
				copdo<jarvis_obj::DrivingOffset::value_type> drivingLoadcellOffset;
				copdo<jarvis_obj::SteeringOffset::value_type> steeringLoadcellOffset;
				copdo<jarvis_obj::StatusControlParam::value_type> statusControlParam;
			};

			struct output_t {
				copdo<jarvis_obj::ParmPosition1::value_type> parmPosition1;
				copdo<jarvis_obj::ParmPosition2::value_type> parmPosition2;
				copdo<jarvis_obj::ParmPosition3::value_type> parmPosition3;
				copdo<jarvis_obj::ParmPosition4::value_type> parmPosition4;
				copdo<jarvis_obj::ParmPosition5::value_type> parmPosition5;
				copdo<jarvis_obj::DrivingLoadcellValue::value_type> drivingLoadcellValue;
				copdo<jarvis_obj::SteeringLoadcellValue::value_type> steeringLoadcellValue;
				copdo<jarvis_obj::DrivingLoadcellValue::value_type> drivingLoadcellScaled;
				copdo<jarvis_obj::SteeringLoadcellValue::value_type> steeringLoadcellScaled;
				copdo<jarvis_obj::SubSystemStatus::value_type> subSystemStatus;
				copdo<jarvis_obj::DrivingSystemStatus::value_type> drivingSystemStatus;
			};

			jarvis() = delete;

			jarvis(comst& mst, const uint16_t id, const uint32_t input_addr, const uint32_t output_addr) :
				base(mst, id),
				_input {
					copdo<jarvis_obj::ControlParam::value_type>(mst, comst::in, input_addr + 0x00u),
					copdo<jarvis_obj::DrivingOffset::value_type>(mst,comst::in, input_addr + 0x20u),
					copdo<jarvis_obj::SteeringOffset::value_type>(mst,comst::in, input_addr + 0x40u),
					copdo<jarvis_obj::StatusControlParam::value_type>(mst,comst::in, input_addr + 0x60u)
				},
				_output {
					copdo<jarvis_obj::ParmPosition1::value_type>(mst, comst::out, output_addr + 0x000u),
					copdo<jarvis_obj::ParmPosition2::value_type>(mst, comst::out, output_addr + 0x020u),
					copdo<jarvis_obj::ParmPosition3::value_type>(mst, comst::out, output_addr + 0x040u),
					copdo<jarvis_obj::ParmPosition4::value_type>(mst, comst::out, output_addr + 0x060u),
					copdo<jarvis_obj::ParmPosition5::value_type>(mst, comst::out, output_addr + 0x080u),
					copdo<jarvis_obj::DrivingLoadcellValue::value_type>(mst, comst::out, output_addr + 0x0a0u),
					copdo<jarvis_obj::SteeringLoadcellValue::value_type>(mst, comst::out, output_addr + 0x0c0u),
					copdo<jarvis_obj::DrivingLoadcellScaled::value_type>(mst, comst::out, output_addr + 0x0e0u),
					copdo<jarvis_obj::SteeringLoadcellScaled::value_type>(mst, comst::out, output_addr + 0x100u),
					copdo<jarvis_obj::SubSystemStatus::value_type>(mst, comst::out, output_addr + 0x120u),
					copdo<jarvis_obj::DrivingSystemStatus::value_type>(mst, comst::out, output_addr + 0x140u)
				} { }

			virtual ~jarvis() { }

			virtual const char* init() override { return nullptr; }
			virtual const char* fini() override { return nullptr; }

			virtual void update(ssi::comst& m, const ssi::comst::sync_done& e) override { }

			input_t& input() { return _input; }
			output_t& output() { return _output; }

			jarvis_obj::StatusControlParam::data in() {
				jarvis_obj::StatusControlParam::data dat;
				dat.value = input().statusControlParam.read();
				return dat;
			}

		private:
			input_t _input;
			output_t _output;
		};
	}
}

#endif // __SSI_NODE_JARVIS_H__

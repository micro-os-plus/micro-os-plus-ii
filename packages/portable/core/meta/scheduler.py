# -*- coding: utf-8 -*-

# This file is part of the µOS++ SE distribution.
# Copyright (c) 2013 Liviu Ionescu.

Component(
     id='component.os.portable.core.scheduler',
     name='Core scheduler definitions',
     description='.',
     
     isEnabled=True,

     sourceFiles=[
         'Stack.cpp',
         'Scheduler.cpp',
         'Thread.cpp',
         'IdleThread.cpp',
         'TimerBase.cpp',
         'TimerTicks.cpp',
         'Mutex.cpp',
     ],

     headerDefinition='OS_INCLUDE_PORTABLE_CORE_SCHEDULER',

     children=[

         Option(
             id='component.os.portable.core.scheduler.maxuserthreads',
             name='The max number of user threads',
             description='.',
             
             isEnabled=True,
             
             headerFile='include/portable/core/include/XCDL_SchedulerDefines.h',
             headerDefinition='OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS',
             
             valueType='int',
             defaultValue='0',                    
         ),

         Option(
             id='component.os.portable.core.scheduler.systemthreads',
             name='The number of system threads',
             description='.',
             
             isEnabled=True,
             
             headerFile='include/portable/core/include/XCDL_SchedulerDefines.h',
             headerDefinition='OS_INTEGER_CORE_SCHEDULER_SYSTEMTHREADS',
             
             valueType='int',
             defaultValue='2',                    
         ),

         Option(
             id='component.os.portable.core.scheduler.timertickssize',
             name='The size of timer ticks storage',
             description='.',
             
             isEnabled=True,
             
             headerFile='include/portable/core/include/XCDL_SchedulerDefines.h',
             headerDefinition='OS_INTEGER_CORE_SCHEDULER_TIMERTICKSSIZE',
             
             valueType='int',
             defaultValue='valueOf("OS_INTEGER_CORE_SCHEDULER_SYSTEMTHREADS")+valueOf("OS_INTEGER_CORE_SCHEDULER_MAXUSERTHREADS")',                    
         ),

         Option(
             id='component.os.portable.core.scheduler.tickspersecond',
             name='The number of scheduler switches per second.',
             description='.',
             
             isEnabled=True,
             
             headerFile='include/portable/core/include/XCDL_SchedulerDefines.h',
             headerDefinition='OS_INTEGER_CORE_SCHEDULER_TICKSPERSECOND',
             
             valueType='int',
             defaultValue='1000',                    
         ),

         Component(
             id='component.os.portable.core.scheduler.custom',
             name='Custom scheduler',
             description='.',
             
             isEnabled=False,
             
             headerDefinition='OS_INCLUDE_CORE_SCHEDULER_CUSTOM',

             children=[

                 Option(
                     id='option.os.portable.core.scheduler.custom.header',
                     name='The path to the scheduler header file',
                     description='.',
                     
                     isEnabled=True,
                     
                     headerDefinition='OS_STRING_CORE_SCHEDULER_CUSTOM_HEADER',
                     
                     valueType='string',
                     defaultValue='must be set',                    
                 ),
                       
             ],
         ),
               
     ],
),
              
# Profinet RT Class 1 simulator based on OMNet++

Simulator used in "A Profinet Simulator for the Digital Twin of Networked Electrical Drive Systems" by A. Morato, S. Vitturi, T. Fedullo, G. Peserico and F. Tramarin.

```
@INPROCEEDINGS{9212017,
  author={A. {Morato} and S. {Vitturi} and T. {Fedullo} and G. {Peserico} and F. {Tramarin}},
  booktitle={2020 25th IEEE International Conference on Emerging Technologies and Factory Automation (ETFA)}, 
  title={A Profinet Simulator for the Digital Twin of Networked Electrical Drive Systems}, 
  year={2020},
  volume={1},
  number={},
  pages={1099-1102},
  doi={10.1109/ETFA46521.2020.9212017}}

```

- The simulator needs a patch on the INET library. Please replace /inet/src/inet/common/ProtocolGroup.cc with the one provided in the inet_patch folder
- If you have problem with INET header refers to https://stackoverflow.com/questions/45271108/omnet-simulating-a-project-that-references-inet-cannot-load-library-libinet
- If you have problems with custom messages, add `MSGC:=$(MSGC) --msg6` in  `project` | `Properties`, select `OMNeT++` | `Makemake` | src folder | `Options...` | `Custom`. Refers to https://stackoverflow.com/questions/56005709/try-to-create-new-project-with-inet-reference-got-unexpected-name-expecting
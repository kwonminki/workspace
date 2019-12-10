/*
 * Filter Coefficients (C Source) generated by the Filter Design and Analysis Tool
 * Generated by MATLAB(R) 9.6 and Signal Processing Toolbox 8.2.
 * Generated on: 08-Dec-2019 19:01:01
 */

/*
 * �̻�ð� FIR ����(�Ǽ�)
 * ---------------
 * ���� ����  : Direct-Form FIR
 * ���� ����  : 597
 * ������    : ��
 * ���� ����  : �� (Type 1)
 */

/* General type conversion for MATLAB generated C-code  *//*
 * Expected path to tmwtypes.h 
 * C:\Program Files\MATLAB\R2019a\extern\include\tmwtypes.h 
 */
#define N2 600
const float h2[600] = {0,0,
   -0.01301440564206,  0.01067652698495,  0.00631714343886, 0.003153425563985,
  0.0009368072068432,-0.0005390999261768,-0.001444497137155, -0.00191917056452,
  -0.002076471106771,-0.002008684289862,-0.001788796267782,-0.001475095713786,
  -0.001112242707556,-0.0007351063086497,-0.0003687413917451,-3.160324757115e-05,
  0.0002643672671039,0.0005114949665195,0.0007062135146233,0.0008477551793899,
  0.0009379558460189,0.0009800888510821,0.0009788070844232,0.0009392269631551,
   0.000867435191175,0.0007693210061814, 0.000651197933339,0.0005185287711618,
  0.0003773013896586,0.0002322053876808,8.831952614813e-05,-5.066998088685e-05,
  -0.0001806824263626,-0.0002992379443411,-0.0004034226453393,-0.0004917989895319,
  -0.0005625498618388,-0.000615185924035,-0.0006489869704944,-0.0006644130917246,
  -0.0006614122733747,-0.0006414288396665,-0.0006049582614339,-0.0005542847944851,
  -0.0004899336945981,-0.0004155211462689,-0.0003295988837189,-0.0002425835301668,
  -0.0001384914951538,-5.448549681062e-05,6.063246569035e-05,0.0001451016406379,
  0.0002358240687168,0.0003315323664897, 0.000402933962985,0.0004651850423481,
  0.0005271861686874,0.0005746039548591,0.0005991718964072,0.0006119656341013,
  0.0006172093851576,0.0006083406597976,0.0005788317952232,0.0005336917444049,
  0.0004794509064953,0.0004174560421338,0.0003437953620698,0.0002575776124273,
   0.000162796044536,6.557684365382e-05,-3.130480140507e-05,-0.0001280826576791,
  -0.0002255895307018,-0.0003213534540618,-0.0004111476526061,-0.0004903646839973,
  -0.0005574169887638,-0.0006120444624318,-0.0006551575387332,-0.0006853115463192,
  -0.0007005084106736,-0.0006981796561057,-0.0006780708565454,-0.0006407950442184,
  -0.0005885735475202,-0.0005229232605165,-0.000445091145785,-0.0003554448567832,
  -0.0002550401895878,-0.000145275673703,-2.945620657493e-05,8.939303572819e-05,
  0.0002072183550133,0.0003221239872236,0.0004302981993237,0.0005328707115302,
  0.0006228384839613,0.0007058270053725,0.0007678175529026,0.0008195023920407,
  0.0008473130601444,0.0008560370859487,0.0008478125351353,0.0008152508200263,
  0.0007652719038082,0.0006991356067977, 0.000612897586533,0.0005096231735373,
  0.0003946686943846,0.0002662251854968,0.0001264245459716,-1.836746747601e-05,
  -0.0001640278583327,-0.0003099549547183,-0.0004526114754423,-0.0005862766369071,
  -0.0007082484923278,-0.0008178306521067,-0.0009123928719977,-0.0009873355248409,
  -0.001039735392839,-0.001069120919008,-0.001074812039722,-0.001055252850009,
    -0.0010091289717,-0.0009377134253711,-0.0008433582050121,-0.0007285077718969,
  -0.0005941629539604,-0.0004423026636132,-0.0002762009927572,-0.0001002955382789,
  8.167770966649e-05,0.0002661535367882,0.0004494796586017,0.0006271515371811,
  0.0007939964651227, 0.000945109102174, 0.001077105594886, 0.001186973884084,
   0.001272442488259, 0.001330191810376, 0.001358547935398, 0.001354667900606,
   0.001320725111266, 0.001253757771306, 0.001158802066862, 0.001031726908619,
  0.0008791688973395,0.0007008045619613, 0.000501167370979,0.0002871266848792,
  5.985554991669e-05,-0.0001732298685665,-0.000407161869435,-0.0006383238746223,
  -0.0008599608563667,-0.001065258075283, -0.00125171689402,-0.001413636020744,
  -0.001545685055701,-0.001645686986868, -0.00171101300261,-0.001737581935076,
  -0.001723239575352,-0.001668765381106,-0.001574122921306,-0.001439783408882,
  -0.001268638753723,-0.001064749871621,-0.0008313331991926,-0.0005720518671099,
  -0.0002930833607915,-1.085415911783e-06,0.0002976804431048,0.0005972256847418,
  0.0008901324061109, 0.001169343375087, 0.001428357408524, 0.001661384194596,
   0.001862202832216, 0.002024674297929, 0.002143557488864, 0.002215492497172,
   0.002238251863804, 0.002209776317362, 0.002128840760553, 0.001996401054358,
   0.001814297224902, 0.001585860099904,  0.00131436155278, 0.001005506959409,
  0.0006643121527696,0.0003001825772677,-8.133791991496e-05,-0.000469612842176,
  -0.0008587251988648,-0.001238129813991,-0.001599303814152,-0.001933705535501,
  -0.002231225154637,-0.002486178414079,-0.002690386898776,-0.002837423858345,
  -0.002922652347782,-0.002942250905405,-0.002893576125298,-0.002777542588034,
  -0.002593917099763,-0.002344149990466, -0.00203330012132,-0.001666290261116,
   -0.00124976522816,-0.0007923807696347,-0.0003040034698502,0.0002064712099534,
  0.0007279364560795, 0.001247873070749, 0.001754472419779, 0.002236551747226,
    0.00268210305269, 0.003079137600068, 0.003417618697123, 0.003688059857973,
   0.003881525052636, 0.003990707985455, 0.004011120906724, 0.003939508697867,
   0.003773979025294, 0.003515192729706, 0.003166264210739, 0.002731979698867,
   0.002218936100463, 0.001636214676196,0.0009948569659757,0.0003074786800464,
  -0.0004118835392519,-0.001148771176898, -0.00188662553552,-0.002608678075966,
  -0.003297343579059,-0.003937307424872,-0.004510633845128,-0.005003039989845,
  -0.005398661279119,-0.005685643414159,-0.005852612713794,-0.005890113841719,
  -0.005792219758604,-0.005554366668067,-0.005177182443164,-0.004662243630585,
  -0.004014750043382, -0.00324276233742,-0.002357807820414,-0.001373615717745,
  -0.0003081846578957,0.0008191002299423, 0.001987263604567,  0.00317166579491,
   0.004347909957295, 0.005489148251759,  0.00656811994073,  0.00755750790191,
   0.008431113656939,  0.00916182547973, 0.009724223918237,     0.01009579764,
    0.01025588273253,  0.01018578753349, 0.009870250148527, 0.009297959223409,
   0.008460379674067, 0.007353413606373, 0.005978057681284, 0.004339374457956,
   0.002445584896008,0.0003096164683525,-0.002050320178197,-0.004612600196402,
  -0.007352374399718, -0.01024097889276, -0.01324648961989, -0.01633503201341,
   -0.01947048893168, -0.02261443224174, -0.02572847169725, -0.02877337574048,
   -0.03171064126258, -0.03450164264169, -0.03711063857953, -0.03950182614991,
   -0.04164457729198, -0.04350962231561, -0.04507140907141, -0.04630898199383,
    -0.0472052618006, -0.04774845792839,   0.9520697823586, -0.04774845792839,
    -0.0472052618006, -0.04630898199383, -0.04507140907141, -0.04350962231561,
   -0.04164457729198, -0.03950182614991, -0.03711063857953, -0.03450164264169,
   -0.03171064126258, -0.02877337574048, -0.02572847169725, -0.02261443224174,
   -0.01947048893168, -0.01633503201341, -0.01324648961989, -0.01024097889276,
  -0.007352374399718,-0.004612600196402,-0.002050320178197,0.0003096164683525,
   0.002445584896008, 0.004339374457956, 0.005978057681284, 0.007353413606373,
   0.008460379674067, 0.009297959223409, 0.009870250148527,  0.01018578753349,
    0.01025588273253,     0.01009579764, 0.009724223918237,  0.00916182547973,
   0.008431113656939,  0.00755750790191,  0.00656811994073, 0.005489148251759,
   0.004347909957295,  0.00317166579491, 0.001987263604567,0.0008191002299423,
  -0.0003081846578957,-0.001373615717745,-0.002357807820414, -0.00324276233742,
  -0.004014750043382,-0.004662243630585,-0.005177182443164,-0.005554366668067,
  -0.005792219758604,-0.005890113841719,-0.005852612713794,-0.005685643414159,
  -0.005398661279119,-0.005003039989845,-0.004510633845128,-0.003937307424872,
  -0.003297343579059,-0.002608678075966, -0.00188662553552,-0.001148771176898,
  -0.0004118835392519,0.0003074786800464,0.0009948569659757, 0.001636214676196,
   0.002218936100463, 0.002731979698867, 0.003166264210739, 0.003515192729706,
   0.003773979025294, 0.003939508697867, 0.004011120906724, 0.003990707985455,
   0.003881525052636, 0.003688059857973, 0.003417618697123, 0.003079137600068,
    0.00268210305269, 0.002236551747226, 0.001754472419779, 0.001247873070749,
  0.0007279364560795,0.0002064712099534,-0.0003040034698502,-0.0007923807696347,
   -0.00124976522816,-0.001666290261116, -0.00203330012132,-0.002344149990466,
  -0.002593917099763,-0.002777542588034,-0.002893576125298,-0.002942250905405,
  -0.002922652347782,-0.002837423858345,-0.002690386898776,-0.002486178414079,
  -0.002231225154637,-0.001933705535501,-0.001599303814152,-0.001238129813991,
  -0.0008587251988648,-0.000469612842176,-8.133791991496e-05,0.0003001825772677,
  0.0006643121527696, 0.001005506959409,  0.00131436155278, 0.001585860099904,
   0.001814297224902, 0.001996401054358, 0.002128840760553, 0.002209776317362,
   0.002238251863804, 0.002215492497172, 0.002143557488864, 0.002024674297929,
   0.001862202832216, 0.001661384194596, 0.001428357408524, 0.001169343375087,
  0.0008901324061109,0.0005972256847418,0.0002976804431048,-1.085415911783e-06,
  -0.0002930833607915,-0.0005720518671099,-0.0008313331991926,-0.001064749871621,
  -0.001268638753723,-0.001439783408882,-0.001574122921306,-0.001668765381106,
  -0.001723239575352,-0.001737581935076, -0.00171101300261,-0.001645686986868,
  -0.001545685055701,-0.001413636020744, -0.00125171689402,-0.001065258075283,
  -0.0008599608563667,-0.0006383238746223,-0.000407161869435,-0.0001732298685665,
  5.985554991669e-05,0.0002871266848792, 0.000501167370979,0.0007008045619613,
  0.0008791688973395, 0.001031726908619, 0.001158802066862, 0.001253757771306,
   0.001320725111266, 0.001354667900606, 0.001358547935398, 0.001330191810376,
   0.001272442488259, 0.001186973884084, 0.001077105594886, 0.000945109102174,
  0.0007939964651227,0.0006271515371811,0.0004494796586017,0.0002661535367882,
  8.167770966649e-05,-0.0001002955382789,-0.0002762009927572,-0.0004423026636132,
  -0.0005941629539604,-0.0007285077718969,-0.0008433582050121,-0.0009377134253711,
    -0.0010091289717,-0.001055252850009,-0.001074812039722,-0.001069120919008,
  -0.001039735392839,-0.0009873355248409,-0.0009123928719977,-0.0008178306521067,
  -0.0007082484923278,-0.0005862766369071,-0.0004526114754423,-0.0003099549547183,
  -0.0001640278583327,-1.836746747601e-05,0.0001264245459716,0.0002662251854968,
  0.0003946686943846,0.0005096231735373, 0.000612897586533,0.0006991356067977,
  0.0007652719038082,0.0008152508200263,0.0008478125351353,0.0008560370859487,
  0.0008473130601444,0.0008195023920407,0.0007678175529026,0.0007058270053725,
  0.0006228384839613,0.0005328707115302,0.0004302981993237,0.0003221239872236,
  0.0002072183550133,8.939303572819e-05,-2.945620657493e-05,-0.000145275673703,
  -0.0002550401895878,-0.0003554448567832,-0.000445091145785,-0.0005229232605165,
  -0.0005885735475202,-0.0006407950442184,-0.0006780708565454,-0.0006981796561057,
  -0.0007005084106736,-0.0006853115463192,-0.0006551575387332,-0.0006120444624318,
  -0.0005574169887638,-0.0004903646839973,-0.0004111476526061,-0.0003213534540618,
  -0.0002255895307018,-0.0001280826576791,-3.130480140507e-05,6.557684365382e-05,
   0.000162796044536,0.0002575776124273,0.0003437953620698,0.0004174560421338,
  0.0004794509064953,0.0005336917444049,0.0005788317952232,0.0006083406597976,
  0.0006172093851576,0.0006119656341013,0.0005991718964072,0.0005746039548591,
  0.0005271861686874,0.0004651850423481, 0.000402933962985,0.0003315323664897,
  0.0002358240687168,0.0001451016406379,6.063246569035e-05,-5.448549681062e-05,
  -0.0001384914951538,-0.0002425835301668,-0.0003295988837189,-0.0004155211462689,
  -0.0004899336945981,-0.0005542847944851,-0.0006049582614339,-0.0006414288396665,
  -0.0006614122733747,-0.0006644130917246,-0.0006489869704944,-0.000615185924035,
  -0.0005625498618388,-0.0004917989895319,-0.0004034226453393,-0.0002992379443411,
  -0.0001806824263626,-5.066998088685e-05,8.831952614813e-05,0.0002322053876808,
  0.0003773013896586,0.0005185287711618, 0.000651197933339,0.0007693210061814,
   0.000867435191175,0.0009392269631551,0.0009788070844232,0.0009800888510821,
  0.0009379558460189,0.0008477551793899,0.0007062135146233,0.0005114949665195,
  0.0002643672671039,-3.160324757115e-05,-0.0003687413917451,-0.0007351063086497,
  -0.001112242707556,-0.001475095713786,-0.001788796267782,-0.002008684289862,
  -0.002076471106771, -0.00191917056452,-0.001444497137155,-0.0005390999261768,
  0.0009368072068432, 0.003153425563985,  0.00631714343886,  0.01067652698495,
   -0.01301440564206,0
};
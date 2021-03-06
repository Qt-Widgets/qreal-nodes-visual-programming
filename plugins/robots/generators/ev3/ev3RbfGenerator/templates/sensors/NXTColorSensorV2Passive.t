// return passive data in format ARRAY32 4 [R,G,B,W]
// TODO unify with Raw (almost same, except first INPUT_DEVICE call)
ARRAY8 ar@@RANDOM_ID_1@@ 4
ARRAY(CREATE8, 4, ar@@RANDOM_ID_1@@)

//enables passive (without lights)
ARRAY_WRITE(ar@@RANDOM_ID_1@@, 0, 1)
ARRAY_WRITE(ar@@RANDOM_ID_1@@, 1, 65)
ARRAY_WRITE(ar@@RANDOM_ID_1@@, 2, 1)
INPUT_DEVICE(SETUP, 0, @@PORT@@, 1, 0, 3, @ar@@RANDOM_ID_1@@, 0, @ar@@RANDOM_ID_1@@)
TIMER_WAIT(110, timer)
TIMER_READY(timer)

ARRAY_WRITE(ar@@RANDOM_ID_1@@, 0, 1)
ARRAY_WRITE(ar@@RANDOM_ID_1@@, 1, 66)

ARRAY8 answer@@RANDOM_ID_2@@ 8
ARRAY(CREATE8, 8, answer@@RANDOM_ID_2@@)

ARRAY32 answerBuf@@RANDOM_ID_3@@ 8
ARRAY(CREATE32, 8, answerBuf@@RANDOM_ID_3@@)
DATA8 tmp@@RANDOM_ID_4@@
DATA32 tmp32@@RANDOM_ID_5@@
ARRAY32 answerRes@@RANDOM_ID_6@@ 4
ARRAY(CREATE32, 4, answerRes@@RANDOM_ID_6@@)

//read raw 8 byte
INPUT_DEVICE(SETUP, 0, @@PORT@@, 1, 0, 2, @ar@@RANDOM_ID_1@@, 8, @answer@@RANDOM_ID_2@@)
// reverse and make uint TODO: REWRITE TO LOOP!!!
ARRAY_READ(answer@@RANDOM_ID_2@@, 0, tmp@@RANDOM_ID_4@@)
CALL(B2U32_EV3_KERNEL_util, tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerBuf@@RANDOM_ID_3@@, 7, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 1, tmp@@RANDOM_ID_4@@)
CALL(B2U32_EV3_KERNEL_util, tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerBuf@@RANDOM_ID_3@@, 6, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 2, tmp@@RANDOM_ID_4@@)
CALL(B2U32_EV3_KERNEL_util, tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerBuf@@RANDOM_ID_3@@, 5, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 3, tmp@@RANDOM_ID_4@@)
CALL(B2U32_EV3_KERNEL_util, tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerBuf@@RANDOM_ID_3@@, 4, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 4, tmp@@RANDOM_ID_4@@)
CALL(B2U32_EV3_KERNEL_util, tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerBuf@@RANDOM_ID_3@@, 3, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 5, tmp@@RANDOM_ID_4@@)
CALL(B2U32_EV3_KERNEL_util, tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerBuf@@RANDOM_ID_3@@, 2, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 6, tmp@@RANDOM_ID_4@@)
CALL(B2U32_EV3_KERNEL_util, tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerBuf@@RANDOM_ID_3@@, 1, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answer@@RANDOM_ID_2@@, 7, tmp@@RANDOM_ID_4@@)
CALL(B2U32_EV3_KERNEL_util, tmp@@RANDOM_ID_4@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerBuf@@RANDOM_ID_3@@, 0, tmp32@@RANDOM_ID_5@@)

// ok now we have right ordered array of uint8 in array32, here we build 16bit array32. TODO: REWRITE TO LOOP!!!
DATA32 tmp232@@RANDOM_ID_7@@
ARRAY_READ(answerBuf@@RANDOM_ID_3@@, 0, tmp32@@RANDOM_ID_5@@)
ARRAY_READ(answerBuf@@RANDOM_ID_3@@, 1, tmp232@@RANDOM_ID_7@@)
MUL32(tmp32@@RANDOM_ID_5@@, 256, tmp32@@RANDOM_ID_5@@)
ADD32(tmp32@@RANDOM_ID_5@@, tmp232@@RANDOM_ID_7@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerRes@@RANDOM_ID_6@@, 0, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answerBuf@@RANDOM_ID_3@@, 2, tmp32@@RANDOM_ID_5@@)
ARRAY_READ(answerBuf@@RANDOM_ID_3@@, 3, tmp232@@RANDOM_ID_7@@)
MUL32(tmp32@@RANDOM_ID_5@@, 256, tmp32@@RANDOM_ID_5@@)
ADD32(tmp32@@RANDOM_ID_5@@, tmp232@@RANDOM_ID_7@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerRes@@RANDOM_ID_6@@, 1, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answerBuf@@RANDOM_ID_3@@, 4, tmp32@@RANDOM_ID_5@@)
ARRAY_READ(answerBuf@@RANDOM_ID_3@@, 5, tmp232@@RANDOM_ID_7@@)
MUL32(tmp32@@RANDOM_ID_5@@, 256, tmp32@@RANDOM_ID_5@@)
ADD32(tmp32@@RANDOM_ID_5@@, tmp232@@RANDOM_ID_7@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerRes@@RANDOM_ID_6@@, 2, tmp32@@RANDOM_ID_5@@)

ARRAY_READ(answerBuf@@RANDOM_ID_3@@, 6, tmp32@@RANDOM_ID_5@@)
ARRAY_READ(answerBuf@@RANDOM_ID_3@@, 7, tmp232@@RANDOM_ID_7@@)
MUL32(tmp32@@RANDOM_ID_5@@, 256, tmp32@@RANDOM_ID_5@@)
ADD32(tmp32@@RANDOM_ID_5@@, tmp232@@RANDOM_ID_7@@, tmp32@@RANDOM_ID_5@@)
ARRAY_WRITE(answerRes@@RANDOM_ID_6@@, 3, tmp32@@RANDOM_ID_5@@)

ARRAY(DELETE, answer@@RANDOM_ID_2@@)
ARRAY(DELETE, ar@@RANDOM_ID_1@@)
ARRAY(DELETE, answerBuf@@RANDOM_ID_3@@)

CALL(assign32Array_EV3_KERNEL_util, answerRes@@RANDOM_ID_6@@, @@RESULT@@)
ARRAY(DELETE, answerRes@@RANDOM_ID_6@@)

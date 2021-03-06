#include <iostream>
#include <jni.h>
#include "interop.hh"
#include "../interop.hh"
#include "DartTypes.h"
#include "Paragraph.h"


using namespace std;
using namespace skia::textlayout;

static void deleteParagraph(Paragraph* instance) {
    delete instance;
}

extern "C" JNIEXPORT jlong JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetFinalizer
  (JNIEnv* env, jclass jclass) {
    return static_cast<jlong>(reinterpret_cast<uintptr_t>(&deleteParagraph));
}

extern "C" JNIEXPORT jfloat JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetMaxWidth
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->getMaxWidth();
}

extern "C" JNIEXPORT jfloat JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetHeight
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->getHeight();
}

extern "C" JNIEXPORT jfloat JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetMinIntrinsicWidth
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->getMinIntrinsicWidth();
}

extern "C" JNIEXPORT jfloat JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetMaxIntrinsicWidth
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->getMaxIntrinsicWidth();
}

extern "C" JNIEXPORT jfloat JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetAlphabeticBaseline
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->getAlphabeticBaseline();
}

extern "C" JNIEXPORT jfloat JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetIdeographicBaseline
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->getIdeographicBaseline();
}

extern "C" JNIEXPORT jfloat JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetLongestLine
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->getLongestLine();
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nDidExceedMaxLines
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->didExceedMaxLines();
}

extern "C" JNIEXPORT void JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nLayout
  (JNIEnv* env, jclass jclass, jlong ptr, jfloat width) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    instance->layout(width);
}

extern "C" JNIEXPORT void JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nPaint
  (JNIEnv* env, jclass jclass, jlong ptr, jlong canvasPtr, jfloat x, jfloat y) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    SkCanvas* canvas = reinterpret_cast<SkCanvas*>(static_cast<uintptr_t>(canvasPtr));
    instance->paint(canvas, x, y);
}

extern "C" JNIEXPORT jobjectArray JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetRectsForRange
  (JNIEnv* env, jclass jclass, jlong ptr, jint start, jint end, jint rectHeightStyle, jint rectWidthStyle) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    std::vector<TextBox> rects = instance->getRectsForRange(start, end, static_cast<RectHeightStyle>(rectHeightStyle), static_cast<RectWidthStyle>(rectWidthStyle));
    jobjectArray rectsArray = env->NewObjectArray(rects.size(), skija::paragraph::TextBox::cls, nullptr);
    for (int i = 0; i < rects.size(); ++i) {
        TextBox box = rects[i];
        jobject boxObj = env->NewObject(skija::paragraph::TextBox::cls, skija::paragraph::TextBox::ctor, box.rect.fLeft, box.rect.fTop, box.rect.fRight, box.rect.fBottom, static_cast<jint>(box.direction));
        env->SetObjectArrayElement(rectsArray, i, boxObj);
    }
    return rectsArray;
}

extern "C" JNIEXPORT jobjectArray JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetRectsForPlaceholders
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    std::vector<TextBox> rects = instance->getRectsForPlaceholders();
    jobjectArray rectsArray = env->NewObjectArray(rects.size(), skija::paragraph::TextBox::cls, nullptr);
    for (int i = 0; i < rects.size(); ++i) {
        TextBox box = rects[i];
        jobject boxObj = env->NewObject(skija::paragraph::TextBox::cls, skija::paragraph::TextBox::ctor, box.rect.fLeft, box.rect.fTop, box.rect.fRight, box.rect.fBottom, static_cast<jint>(box.direction));
        env->SetObjectArrayElement(rectsArray, i, boxObj);
    }
    return rectsArray;
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetGlyphPositionAtCoordinate
  (JNIEnv* env, jclass jclass, jlong ptr, jfloat dx, jfloat dy) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    PositionWithAffinity p = instance->getGlyphPositionAtCoordinate(dx, dy);
    if (p.affinity == Affinity::kDownstream)
        return p.position;
    else
        return -p.position-1;
}

extern "C" JNIEXPORT jlong JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetWordBoundary
  (JNIEnv* env, jclass jclass, jlong ptr, jint offset) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    SkRange<size_t> range = instance->getWordBoundary(offset);
    return (range.start << 32) | (range.end & 0xFFFFFFFF);
}

extern "C" JNIEXPORT jobjectArray JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetLineMetrics
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    std::vector<LineMetrics> res;
    instance->getLineMetrics(res);
    jobjectArray resArray = env->NewObjectArray(res.size(), skija::paragraph::LineMetrics::cls, nullptr);
    for (int i = 0; i < res.size(); ++i) {
        LineMetrics lm = res[i];
        jobject lmObj = env->NewObject(skija::paragraph::LineMetrics::cls, skija::paragraph::LineMetrics::ctor, lm.fStartIndex, lm.fEndIndex, lm.fEndExcludingWhitespaces, lm.fEndIncludingNewline, lm.fHardBreak, lm.fAscent, lm.fDescent, lm.fUnscaledAscent, lm.fHeight, lm.fWidth, lm.fLeft, lm.fBaseline, lm.fLineNumber);
        env->SetObjectArrayElement(resArray, i, lmObj);
    }
    return resArray;
}

extern "C" JNIEXPORT jlong JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetLineNumber
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->lineNumber();
}

extern "C" JNIEXPORT void JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nMarkDirty
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->markDirty();
}

extern "C" JNIEXPORT jint JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nGetUnresolvedGlyphsCount
  (JNIEnv* env, jclass jclass, jlong ptr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->unresolvedGlyphs();
}

extern "C" JNIEXPORT void JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nUpdateAlignment
  (JNIEnv* env, jclass jclass, jlong ptr, jint textAlignment) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->updateTextAlign(static_cast<TextAlign>(textAlignment));
}

extern "C" JNIEXPORT void JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nUpdateText
  (JNIEnv* env, jclass jclass, jlong ptr, jint from, jstring text) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->updateText(from, skString(env, text));
}

extern "C" JNIEXPORT void JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nUpdateFontSize
  (JNIEnv* env, jclass jclass, jlong ptr, jint from, jint to, jfloat fontSize) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    return instance->updateFontSize(from, to, fontSize);
}

extern "C" JNIEXPORT void JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nUpdateForegroundPaint
  (JNIEnv* env, jclass jclass, jlong ptr, jint from, jint to, jlong paintPtr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    SkPaint* paint = reinterpret_cast<SkPaint*>(static_cast<uintptr_t>(paintPtr));
    return instance->updateForegroundPaint(from, to, *paint);
}

extern "C" JNIEXPORT void JNICALL Java_org_jetbrains_skija_paragraph_Paragraph__1nUpdateBackgroundPaint
  (JNIEnv* env, jclass jclass, jlong ptr, jint from, jint to, jlong paintPtr) {
    Paragraph* instance = reinterpret_cast<Paragraph*>(static_cast<uintptr_t>(ptr));
    SkPaint* paint = reinterpret_cast<SkPaint*>(static_cast<uintptr_t>(paintPtr));
    return instance->updateBackgroundPaint(from, to, *paint);
}

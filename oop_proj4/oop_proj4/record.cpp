#include "record.h";

Record::Record()
{
    // 무압축 소리 데이터 설정
    pFormat.wFormatTag = WAVE_FORMAT_PCM;
    // 소리 채널 수, 1이면 모노, 2이면 스테레오입니다.
    pFormat.nChannels = 2;
    // 샘플링 데이터 횟수.
    // nSamplesPerSec에는 8.0 kHz, 11.025 kHz, 22.05 kHz, 44.1 kHz가 있습니다.
    pFormat.nSamplesPerSec = 44100;
    // WAVE_FORMAT_PCM이라면 무압축이기 때문에 nSamplesPerSec와 같을 것이다.
    pFormat.nAvgBytesPerSec = 44100;
    // 1회 샘플링에 사용되어지는 데이터 비트수, 8 또는 16
    pFormat.wBitsPerSample = 16;
    // 샘플링에 사용되는 바이트 단위의 메모리 크기
    pFormat.nBlockAlign = pFormat.nChannels * (pFormat.wBitsPerSample / 8);
    // WAVE_FORMAT_PCM에서는 무시되는 값
    pFormat.cbSize = 0;
    // waveInOpen는 위 구조체로 장치를 Open하는 함수.
    // 파라미터는 HWAVEIN, 두번째는 장치 선택인데 보통은 WAVE_MAPPER를 넣어도 됩니다.
    // 저는 특이하게 마이크가 여러개 있어서(노트북 기본 마이크, 해드셋 마이크) 가장 나중에 접속한 단자를 선택했습니다.
    // 세번째 파라미터는 음성 포멧을 넣고, call함수를 넣습니다.
    // 마지막 파라미터는 CALLBACK_FUNCTION를 설정해서 callback함수를 사용한다는 것을 설정합니다.
    if (waveInOpen(&hWaveIn, waveInGetNumDevs() - 1 /*WAVE_MAPPER*/, &pFormat, (DWORD_PTR)waveInProc, 0, CALLBACK_FUNCTION)) {
        // 에러 콘솔 출력
        cout << "Failed to open waveform input device." << endl;
        // 접속 실패
        exit(0);
    }

    // 데이터 구조체 설정
    // 버퍼의 길이를 설정한다. 무조건 1초 단위로 설정합니다.
    // 위 구조체에서 샘플링을 44100 바이트로 했기 때문에 그 크기를 넣는다.
    WaveInHdr.dwBufferLength = pFormat.nAvgBytesPerSec;
    // 실제 데이터를 할당한다.
    WaveInHdr.lpData = (char*)malloc(WaveInHdr.dwBufferLength);
    // 라이브러리에서 실제 녹음된 사이즈를 구하는 함수(사용자가 사용하는 값이 아님)
    WaveInHdr.dwBytesRecorded = 0;
    // 라이브러리에서 callback 함수 사용시 사용되는 status flag
    WaveInHdr.dwFlags = 0;
    // 반복 재생시 사용됨 (사용하지 않는다.)
    WaveInHdr.dwLoops = 0;
    // 예약 재생시 사용됨 (사용하지 않는다.)
    WaveInHdr.reserved = 0;
    // 버퍼 설정. 실제 녹음은 1초 단위로 데이터가 나오는데.. 데이터를 연결할 필요가 있다.
    // WaveInHdr.dwUser는 원래 버퍼를 설정하는 변수는 아니지만, 사용하지 않는 변수이기 때문에 재활용
    WaveInHdr.dwUser = (ULONG_PTR)new BufferNode();
    bn = (BufferNode*)WaveInHdr.dwUser;
    // 동적으로 메모리를 재할당하기 때문에 1byte만 할당하자
    bn->buffer = (char*)malloc(1);
    // 초기 데이터 길이는 0이다.
    bn->length = 0;
}

Record::~Record()
{
    // 구조체의 메모리는 동적 할당 되었기 때문에 해제한다. 더이상 필요가 없음.
    delete WaveInHdr.lpData;
    // 동적 할당된 버퍼를 메모리 해제한다.
    delete bn->buffer;
    delete bn;
}

void Record::rec()
{
    // 장치에 녹음 준비를 알리는 함수
    if (waveInPrepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR))) {
        // 에러 콘솔 출력
        cout << "waveInPrepareHeader error" << endl;
        // 장치 닫기
        waveInClose(hWaveIn);
        exit(0);
    }

    // 장치에 메모리를 할당을 하는 함수
    if (waveInAddBuffer(hWaveIn, &WaveInHdr, sizeof(WAVEHDR))) {
        // 에러 콘솔 출력
        cout << "waveInAddBuffer error" << endl;
        // 장치 닫기
        waveInClose(hWaveIn);
        exit(0);
    }

    // 녹음 시작
    if (waveInStart(hWaveIn)) {
        // 에러 콘솔 출력
        cout << "waveInStart error" << endl;
        // 장치 닫기
        waveInClose(hWaveIn);
        exit(0);
    }
    // 콘솔 출력
    cout << "Recording..." << endl;

    // 아무 키를 누르고 엔터를 치면 녹음을 중단하고 바로 파일로 저장한다.
    while (true) {
        cout << "If press any key, the record will save to the file." << endl;
        char input = -1;
        cin >> input;

        if (input != -1)
            break;
    }

    // callback에 종료를 알리는 Flag 설정.
    WaveInHdr.dwFlags = WHDR_DONE;
    // 녹음 종료
    waveInStop(hWaveIn);
    // 장치에 녹음 해제를 알리는 함수
    waveInUnprepareHeader(hWaveIn, &WaveInHdr, sizeof(WAVEHDR));
    // 장치 닫기
    waveInClose(hWaveIn);
    // 버퍼의 데이터를 설정한다.
    WaveInHdr.dwBufferLength = bn->length;
    WaveInHdr.lpData = (char*)bn->buffer;
    // 파일을 저장한다.
    SaveWavFile("C:\Proj4\oop_proj4\record", &pFormat, &WaveInHdr);
}

void CALLBACK Record::waveInProc(HWAVEIN hWaveIn, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
    switch (uMsg) { // 데이터가 호출되면 메시지가 WIM_DATA로 호출된다.
    case WIM_DATA:
        // 음성 데이터 구조체 취득
        WAVEHDR* WaveInHdr = (WAVEHDR*)dwParam1;
        // 버퍼를 가져온다.
        BufferNode* bn = (BufferNode*)WaveInHdr->dwUser;
        // WaveInHdr->dwBytesRecorded는 녹음된 사이즈이다.
        // 녹음된 사이즈만큼 메모리 재할당을 한다.
        bn->buffer = realloc(bn->buffer, bn->length + WaveInHdr->dwBytesRecorded);
        // 1초 단위로 샘플링이 오기 때문에 마지막 녹음된 위치의 그 뒤에 메모리 복사를 한다.
        // 1초에는 bn->length가 0이기 때문에 그대로 녹음된 1초가 memcpy함.
        // 2초에는 bn->length가 1초의 길이만큼 들어가니 앞의 1초 뒤에 1초가 memcpy함.
        // 3초는 2초 뒤에...
        memcpy((char*)bn->buffer + bn->length, WaveInHdr->lpData, WaveInHdr->dwBytesRecorded);
        // 길이를 늘려준다.
        bn->length += WaveInHdr->dwBytesRecorded;

        // 장치에 녹음 준비를 알리는 함수
        if (waveInPrepareHeader(hWaveIn, WaveInHdr, sizeof(WAVEHDR))) {
            // 에러 콘솔 출력
            cout << "waveInPrepareHeader error" << endl;
            // 장치 닫기
            waveInClose(hWaveIn);
            return;
        }

        // 장치에 메모리를 할당을 하는 함수
        if (waveInAddBuffer(hWaveIn, WaveInHdr, sizeof(WAVEHDR))) {
            // 에러 콘솔 출력
            cout << "waveInPrepareHeader error" << endl;
            // 장치 닫기
            waveInClose(hWaveIn);
            return;
        }

        break;
    }
}

void Record::SaveWavFile(const char* filename, WAVEFORMATEX* format, PWAVEHDR WaveHeader)
{
    // output stream을 할당
    ofstream ostream;
    // 파일 열기
    ostream.open(filename, fstream::binary);

    int subchunk1size = 16;
    int byteRate = format->nSamplesPerSec * format->nBlockAlign;
    int subchunk2size = WaveHeader->dwBufferLength * format->nChannels;
    int chunksize = (36 + subchunk2size);
    // wav파일 구조체대로 작성한다.
    ostream.seekp(0, ios::beg);
    // chunk id
    ostream.write("RIFF", 4);
    // chunk size (36 + SubChunk2Size))
    ostream.write((char*)&chunksize, 4);
    // format
    ostream.write("WAVE", 4);
    // subchunk1ID
    ostream.write("fmt ", 4);
    // subchunk1size (무압축 PCM이면 16 고정)
    ostream.write((char*)&subchunk1size, 4);
    // AudioFormat (무압축 PCM이면 1 고정)
    ostream.write((char*)&format->wFormatTag, 2);
    // NumChannels
    ostream.write((char*)&format->nChannels, 2);
    // sample rate  
    ostream.write((char*)&format->nSamplesPerSec, 4);
    // byte rate (SampleRate * block align)
    ostream.write((char*)&byteRate, 4);
    // block align
    ostream.write((char*)&format->nBlockAlign, 2);
    // bits per sample
    ostream.write((char*)&format->wBitsPerSample, 2);
    // subchunk2ID
    ostream.write("data", 4);
    // subchunk2size (NumSamples * nBlockAlign)  
    ostream.write((char*)&subchunk2size, 4);
    // 실제 음악 데이터 작성  
    ostream.write(WaveHeader->lpData, WaveHeader->dwBufferLength);
    // 파일 닫기
    ostream.close();
}
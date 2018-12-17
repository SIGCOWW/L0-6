= 俺が好きなのは非接触決済だけどQRコード決済じゃない
@<author>{新卒のぺーぺー, lrks;twitter:__lrks__}
//profile{
最近はJojaコーポレーションを退職後、農作業に励んでいます。
なお求人については引き続き、株式会社イーグルジャンプ、株式会社スルガシステム、ブランクソフトウェアからのご案内をお待ちしております。
併せて奈良素敵大学、きらら女子大学からの公募についてもご案内いただきたいです。
よろしくお願いいたします。
//}


//lead{
この物語は、各種決済を導入したサークルのいきさつを淡々と述べるものです。過度な期待はしないでください。
あと、今回紹介するつもりだった「イシダ製電子棚札の通信プロトコル解析」からは離れて、次回にご期待しやがってください。
//}

== はじめに
締め切りが厳しいです。
社会人で同人誌書いている人、みんな人間辞めているのでは？

さて、人間辞めているといえば当サークルSIGCOWWですが、この度のC95からPayPayと交通系電子マネー決済を導入しました。@<emoji>{congratulations}
これにより、支払い手段として日本円のほか、「クレジットカード」「交通系電子マネー」「QRコード」による決済に対応したことになります。
今回の記事は、これらの支払い手段を導入するにあたっての記録をまとめたものです。




契約している会社を含めてまとめると、@<table>{paymethod}のとおりになりました。
これらはすべて加盟店@<fn>{serval}として登録しています。
//footnote[serval][pixiv PAYの場合、「加盟店」に当たるか微妙ですが見逃してください。]
//tabooular[paymethod][決済方法の一覧]{
決済方法         | 決済代行会社・サービス提供会社
=================|================================
クレジットカード | Square株式会社
クレジットカード | コイニー株式会社
交通系電子マネー | コイニー株式会社
WeChat Pay       | コイニー株式会社
pixiv PAY        | ピクシブ株式会社
PayPay           | PayPay株式会社
//}

本当は、QUICPayやiD、NFC決済（Visa payWave、Mastercard Contactless、JCB Contactless）あたりも導入できていると嬉しかったのですが、「交通系電子マネー」がある時点で上出来でしょう。もう100点満点中99点くらい取れています。
なお、この交通系電子マネーの導入は非常に大変で…という話は次の章で述べるので、ご期待しやがってください。
ちなみに、その次の章はコミケなどの即売会におけるオペレーションについて述べ、最後に今後の展望について述べています。


== 導入までのあれこれ
苦労話パートです。

=== クレジットカード編
「コミケでクレカ決済」といえば？Squareですよ！Square！
ということで、SIGCOWWではSquare株式会社@<fn>{square}が提供するクレジットカード決済を導入しています@<fn>{emoney}。
株式会社Squareによる審査を受ければVisa、Mastercard、AMEXの取り扱いが可能となり、株式会社ジェーシービーによる2次審査の結果次第でJCB、Diners、Discoverの取り扱いが可能です。
//footnote[square][米Square社の日本法人。三井住友カード株式会社と提携している。]
//footnote[emoney][コイニー株式会社の話は交通系電子マネー編でやります。]

個人の感想ですが、Squareに対しては次に示す印象を持ちました。

==== 導入が簡単
Webフォームから加盟店審査を申し込んで終わりです。
他社の場合ですが、「電話かメールで問い合わせてね！（完）」の一文があるだけなことも少なくありません。

==== 加盟店審査が寛大
運が良かっただけかも知れませんが、加盟店審査について比較的容易な印象を受け、苦労は感じませんでした@<fn>{kurou}。
//footnote[kurou][この章は「苦労話パート」なはずだが？]

==== 決済端末が簡素すぎる
日本以外の国ではNFC決済に対応した端末（@<img>{contactless_reader}）をはじめ本格的な決済端末が提供されている一方、日本法人からは簡素な端末（@<img>{chip_card_reader}）しか提供されていません。
スマートフォンやタブレットとの接続について、@<img>{chip_card_reader}は有線（フォーンプラグ）に対し@<img>{contactless_reader}は無線（Bluetooth）となり、電波干渉が心配されるコミケでの利用には配慮が要りそうですが、そもそも選択肢が無いというのは悲しいですね…。
//subfig[Squareが提供する端末]{
//image[contactless_reader][Square_Contactless_and_Chip_Reader][scale=0.49]
//image[chip_card_reader][Square_Chip_Card_Reader][scale=0.49]
//}
#@# Todo: SPだけを出す命令を作る

なお、@<img>{contactless_reader}の端末を輸入して日本国内で利用することも検討しましたが、厳しそうです。
まず、当該端末はスマートフォンやタブレットとBluetoothで接続するのですが、技適マークがありません。
それを見なかったことにしても、日本法人が提供している決済アプリからは当該端末に対応していません。
他国の法人が提供する決済アプリを使うには、その国で有効なアカウントが必要で、そのアカウントは当該国での決済のみ利用できます。
「Square Reader SDK」という決済端末を扱うためのSDKもありますが、日本国内のアカウントでは利用できません。はい論破。

==== サイン必須なのが厄介
Squareによる決済では、どんなに少額でも決済時にサインが必要です。
サインレスどころか、PINコードによる決済もできません@<fn>{pin}。
ちなみに、米国とカナダのアカウントでは$25未満の決済はサインレスで行えます。ぐぬぬ…。
//footnote[pin][国外のアカウントでも同様。Squareの端末にはキーパッドがないため、PINコードはスマートフォンやタブレットの画面に入力させるしかないが、これがPCI (Payment Card Industry)基準を満たせない可能性がある。]


=== QRコード決済編
交通系電子マネー編だと思った？残念！QRコード決済編でした！

「コミケでQRコード決済」といえば？pixiv PAYですよ！pixiv PAY！
ということで、SIGCOWWではpixiv PAYを導入しています。
ただ、pixivのアカウントさえあれば良いので、@<bou>{導入では}苦労話はありません。
その分オペレーションで苦労しつつありますが、この辺の話は後ほど述べます。

次に、WeChat Pay@<fn>{wechatpay}の話です。
積極的に導入しようと思ったわけではなく、コイニー株式会社による決済を導入すると自動的に審査が進み、それに通っただけのことです。特に苦労話はありません。
なお、加盟店として登録されているがゆえに、中国国内で本人確認の済んだアカウントでなければ決済できません。
果たして、利用されることはあるのでしょうか。
//footnote[wechatpay][中国・テンセントが提供するチャットアプリの一機能として提供される支払方法。]

そして、PayPayの話です。
先の2つとは異なり、まともに加盟店審査を受け、導入しました。
導入の理由は半ば消去法ですが、数あるQRコード決済の中でシェアを獲得しそうな割に加盟店審査が甘そうだと考えたからです。
実際導入したところ、次のような印象を持ちました。

==== 加盟店審査の難易度は普通
甘いと思ったら普通でした。
個人で申込可能かつ催事利用可能という話だったため、厳しいわけではありませんでしたが、電話とメールによるやりとりは何度かありました。
業態確認と、「出展の様子を示せ」と言われる例のやつです。

==== サポートが厚い
何かにつけて連絡が来る、すぐ会おうとしてきます。

==== 加盟店登録しなくても良かったかも
PayPayで支払う際の方法には、「よみとる決済」と「みせる決済」という2つがあります。
それぞれ、ユーザが店舗側に置かれたQRコードを@<bou>{読み取る}方法、ユーザが店舗側のPOSレジにQRコードを@<bou>{見せる}という方法です。
#@# TODO: ここに画像貼る、公式サイトのアレを
おそらく、個人や中小企業が運営する店舗の場合は「よみとる決済」、ファミリーマートやヤマダ電機などのチェーン店は「みせる決済」を想定していることでしょう。
もちろんSIGCOWWでは、「よみとる決済」でのみ支払いを受け付けています@<fn>{honto}。
//footnote[honto][本当は「みせる決済」で導入したかった…。「よみとる決済」でもせめて裏にFelica/NFCタグを貼っておいて欲しかった…。店舗側のスマホか何かと非接触で通信できる方法も用意してほしかった…。]

ただ、PayPayには個人間送金の機能があり、これを利用すれば加盟店登録までする必要はなかったのでは…と考えています。
@<table>{paypay}は、加盟店として決済を受け付けた場合と個人間送金機能を利用した場合の比較で、この差をどう考えるかですね。
毎月数万円以上の決済が行われる店舗であれば、決済金額をPayPay残高で受け取っても仕方ないため加盟店登録！これしかないという感じですが…。
//tabooular[paypay][加盟店と個人間送金の比較]{
           | 加盟店                       & 個人間送金
==========>|==============================&============
加盟店審査 | 必要                         & 不要
手数料     | よみとる決済ではしばらく無料 & 無料
支払側還元 | あり（0.5%）                 & なし
支払元     | PayPay残高                   & PayPay残高
           | Yahoo!マネー                 & （特典で付与された分は除く）
           | クレジットカード             &
振込先     | 銀行口座                     & PayPay残高
//}


=== 交通系電子マネー編
いよいよ交通系電子マネー編です。
ようやく苦労話ができます。

ここで述べる交通系電子マネーとは、全国相互利用可能な交通系ICカードのうちPiTaPaを除く9種類、Kitaca、Suica、PASMO、TOICA、manaca、ICOCA、SUGOCA、nimoca、はやかけんのことです。
クレジットカードのようにサインやPINコード入力は不要でスムーズに決済可能なため、コミケ向きです。
しかし、加盟店審査は厳しめで、特に「個人名義での申込み」や「常設店舗なし」「催事利用」ではそれが顕著な印象を受けました。
個人サークルによるコミケでの利用を考えると、役満で絶望的です。
利用側からみれば、あんな駅の券売機でも入手できるカードで、スマートフォンにアプリを入れるだけで使えるような支払い手段なんですけど…。

SIGCOWWでは、最終的にコイニー株式会社@<fn>{coiney}が提供する決済サービスを利用することで、交通系電子マネーの取り扱いに対応しました。
ただ、ここにたどり着くまでには紆余曲折を経ており、まとめると@<table>{suica}のようになります。
//tabooular[suica][交通系電子マネー取り扱いのために申し込んだ記録]{
申し込み時期 | 社名・サービス名 | 結果
============>|==================|<==============
2017年9月    | 楽天ペイ         | 即落ち
2018年7月    | 楽天ペイ（再挑戦）| 出展の様子を求められ提出するも否決
      8月    | Airペイ          | 激落ち
      8月    | R社              | 可決の見込みなしで強制終了
      8月    | A-REGI           | 常設店舗が必要で対象外
      9月    | A社              | 意味のある返事なし
      9月    | United Will      | 何往復かやりとりするも否決
      9月    | J社              | 進行中
      10月   | Coiney           | 可決（クレジットカードのみ）
      12月   | Coiney           | 交通系電子マネー追加審査も可決
//}
//footnote[coiney][モバイル決済サービス「Coiney」を提供する会社。株式会社クレディセゾンと提携している。]

申し込みすぎでは？
この頃のターゲティング広告、「審査に通らない方へ」とかそんな内容ばかりだった気がします。
それでも、もしCoineyが通らなければ、Times Payや、ソフトバンク・ペイメント・サービス株式会社または株式会社シーピーエージェントの決済サービスにも申し込むつもりでいました。

しかし、よく見るとCoineyのところに「可決（クレジットカードのみ）」と書いてあります。
本章は「交通系電子マネー編」のはずでは？
実は、Coineyが交通系電子マネーの取り扱いを開始したのは2018年12月のことです。
最初に申し込んだ2018年10月の段階ではまだ取り扱われていませんでしたが、「Coineyの加盟店になっておくことで、今後訪れるであろう交通系電子マネー取り扱いの追加審査が甘くなるのでは？」と考えました。
本当に甘かったのかは比較のしようがないため分かりませんが、結果的には審査に通ったためOKです。
運が良かったのと、審査前に神社へ参拝したのが効いたのでしょう。マジ神です。

一応、上記とクレジットカードの話を含めてCoineyに対して持った印象を次に述べます。

==== 加盟店審査通過は簡単ではない
交通系電子マネー取り扱い審査の話は置いて、クレジットカード取り扱い審査の話です。
Coineyでは、1次審査としてVisa、Mastercard、また国際ブランドを問わずセゾンカードの取り扱い審査があります。
この段階で、販売業態の確認と販売の様子について確認が入りました。

その後、無事1次審査に通過し、次は2次審査となりました。
2次審査の結果次第で、JCB、AMEX、Diners、Discoverの取り扱い可否が決まります。
加盟店審査が厳しいJCBが入っている時点で不安でしたが、案の定否決でした。おわり。
でも、交通系電子マネーの審査には通ったのでOKです。
肉を切らせて骨を断つですよ。

少なくとも2次審査に関しては株式会社ジェーシービーが行っているものと思いますが、Squareのときは何で通ったのでしょう？@<emoji>{thinking}
最近、JCBのカードで決済したのが、FANZAとDLsite、とら、メロブだけだったためという可能性が95割くらい考えられますね。

==== PINコード入力で決済できる
まだクレジットカードの話です。
Coineyでは、決済に@<img>{terminal_plus}のキーパッドのある端末@<fn>{miura}を利用しており、クレジットカード決済の際にPINコードで取引できます。嬉しい！
ただ、2014年頃まで提供されていた@<img>{coiney_reader}の端末@<fn>{coineyreader}では、1万円以下の決済はサインレスだったそうです。悲しい！
//subfig[Squareが提供する端末]{
//image[terminal_plus][CoineyターミナルPlus][scale=0.49]
//image[coiney_reader][Coineyリーダー][scale=0.3]
//}
//footnote[miura][Miura M010 Reader]
//footnote[coineyreader][決済端末のEMV対応義務化に伴って廃止された。]

==== 交通系電子マネーを取り扱う際のみ制約がある
誰でも閲覧可能なサポートページ@<fn>{coiney-support}によると、いくつか気になる記述がありました。
これらは交通系電子マネーを取り扱う場合のみに限られますが、下記のような具合です。

: 対応端末が限られる
  決済に利用できるスマートフォン・タブレットは、一部のiOS端末に限られます。
  サポート対象になるのは発売から2年以内の端末のみということでした。
  TODO:なお、手元のiPad Air 2はサポート対象外ではあるものの動いたため、しばらくは～今後は～検討しないとだめかも～
: 決済アプリのインストールに制限がある
  決済アプリのインストール回数は1アカウント10回までだそうです。
  おそらく超えないとは思いますが、気をつける必要があります。

//footnote[coiney-support][@<href>{https://support.coiney.com/hc/ja/categories/360001182011}]



== 即売会でのオペレーション
SIGCOWWには、POSレジのようなシステム@<fn>{nichi}があります。
Raspberry Piを中心としてiPadやバーコードリーダー、カスタマディスプレイが接続される構成です。
TODO: ちなみに、iPadのスタンドは〜
//footnote[nichi][@<href>{https://github.com/SIGCOWW/nichi}]

本章では、このシステムと各種決済を連携するあれこれについて述べます。

=== Square
Custom URL Schemeで〜
オフラインでやっておくべきだった〜

=== Coiney
Todo: テスト決済してみよう
Todo: SDKしかない？
Todo: ipaを見てみる

=== pixiv PAY
Todo: 昔やったあれを書く
Todo: アルミ箔テープ？
Todo: ここで電源周りの話までやる、セルフパワーのHubは？
Todo: 商品QR
Todo: Smart Connector

=== PayPay
Todo: ロゴをなんちゃらする
Todo: テスト決済してみよう

== 今後の展望
大きく吸ってせーの
